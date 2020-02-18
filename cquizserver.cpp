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
	for (const auto& client : m_clients)
	{
		qDebug() << "Attempting client" << client.second << "disconnection";
		client.first->disconnectFromHost();
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
	socketPtr socket;

	while ((socket = socketPtr(m_server.nextPendingConnection())))
	{
		connect(socket.get(), &QTcpSocket::disconnected,
				this, &CQuizServer::onClientDisconnected);

		const auto desc = socket->socketDescriptor();
		m_clients.append(socketObj(std::move(socket), desc));

		qDebug() << "Client" << desc << "connected";
	}
}

/**
 * @brief	The slot should be called each time any of
 *			the connected client disconnets.
 */
void CQuizServer::onClientDisconnected()
{
	for (auto i = 0; i < m_clients.size(); i++)
	{
		if (m_clients[i].first->state() == QAbstractSocket::UnconnectedState)
		{
			qDebug() << "Client" << m_clients[i].second << "disconnected";
			m_clients.removeAt(i);
			break;
		}
	}
}



















