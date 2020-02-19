#include <QDebug>

#include "cquizserver.h"

/**
 * @brief	Creates and starts the Quiz server module.
 * @param	port: The port on which the server will be listening to connection.
 * @param	sStart: When set, the server starts at the end of the constructor.
 * @param	parent: the parent object.
 */
CQuizServer::CQuizServer(const int port, const bool sStart, QObject *parent) :
	QObject(parent), m_port{port}
{
	if (sStart)
		start();
}

/**
 * @brief	The class destructor closes all connections.
 */
CQuizServer::~CQuizServer()
{
	qDebug() << __func__ << "destructor called";
	stop();
}

/**
 * @brief	Attempts to start the TCP server and listen to incomming clients
 *			connections.
 * @return	Non zero in case of failure to start the listening.
 */
int CQuizServer::start()
{
	connect(&m_server, &QTcpServer::newConnection,
			this, &CQuizServer::onNewConnections);

	const auto p = static_cast<quint16>(m_port);
	const auto ret = m_server.listen(QHostAddress::Any, p);

	if (ret)
		qDebug() << "Server listening on port" << p;
	else
		qDebug() << "Server starting failed";

	return ret;
}

/**
 * @brief	Disconnects all of the connected clients and stops listening to
 *			new connections.
 */
void CQuizServer::stop()
{
	disconnect(&m_server, &QTcpServer::newConnection,
			this, &CQuizServer::onNewConnections);

	// disconnect all clients
	for (const auto& c : m_clients)
	{
		qDebug() << "Attempting client" << c->descriptor() << "disconnection";
		c->disconnect();
	}

	// close the server
	if (m_server.isListening())
	{
		m_server.close();
		qDebug() << "Server closed";
	}
}

/**
 * @brief	The slot should be called each time new clients connect to the
 *			server.
 */
void CQuizServer::onNewConnections()
{
	SocketPtr socket;

	while ((socket = SocketPtr(m_server.nextPendingConnection())))
	{
		ClientPtr cp;
		if ((cp = makeNextClient(socket)))
			qDebug() << "Client" << cp->descriptor() << "connected";
	}
}

/**
 * @brief	The slot should be called each time any of
 *			the connected client disconnects.
 * @param	desc: socket descriptor of the disconnected client.
 */
void CQuizServer::onClientDisconnected(const qintptr desc)
{
	qDebug() << "Client" << desc << "disconnected from the server";
	removeDeadClients();
}

/**
 * @brief	A new connected socket is added to the list. In case there are
 *			disconnected clients in the list, they are utilized. Otherwise
 *			new one is appended.
 * @param	socket: socket to be tied.
 * @return	Obtains the new client.
 */
ClientPtr CQuizServer::makeNextClient(SocketPtr socket)
{
	ClientPtr cp = std::make_shared<CQuizClient>(socket);
	m_clients.append(cp);

	connect(cp.get(), &CQuizClient::disconnected,
			this, &CQuizServer::onClientDisconnected);

	return cp;
}

/**
 * @brief	Removes all of the diconnected clients from the server cache
 */
void CQuizServer::removeDeadClients()
{
	QMutableListIterator<ClientPtr> i(m_clients);
	while (i.hasNext())
	{
		if (!i.next()->socketConnected())
			i.remove();
	}
}





















