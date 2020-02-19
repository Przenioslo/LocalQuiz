#include "cquizclient.h"

/**
 * @brief	The client constructor takes a connected socket as a parameter and
 *			binds it to its internal member.
 *			socket: the connected socket smart pointer.
 * @param	parent: The parent object pointer.
 */
CQuizClient::CQuizClient(SocketPtr socket, QObject *parent) : QObject(parent)
{
	assignSocket(socket);
}

/**
 * @brief	In the destructor everything is cleaned up, including connections.
 */
CQuizClient::~CQuizClient()
{
	qDebug() << __func__ << "destructor called";

	QObject::disconnect(m_socket.get(), &QTcpSocket::disconnected,
			this, &CQuizClient::onSocketDisconnected);
}

/**
 * @brief	Obtains the socket descriptor from the last connection.
 *			It is retained after a disconnect and is updated on next connection.
 * @return	Socket descriptor. 0 is returned in case it is not valid.
 */
qintptr CQuizClient::descriptor()
{
	return m_descriptor;
}

/**
 * @brief	Disconnects the \ref m_socket from the host if connected.
 */
void CQuizClient::disconnect()
{
	m_socket->disconnectFromHost();
}

/**
 * @brief	Obtains the \ref m_socket status connection
 * @return	Non zero in case socket is connected
 */
bool CQuizClient::socketConnected()
{
	return m_socket->state() == QAbstractSocket::ConnectedState;
}

/**
 * @brief	Assigns the new socket to the client
 * @param	socket: object to be assigned
 */
void CQuizClient::assignSocket(SocketPtr socket)
{
	m_socket = socket;
	if (m_socket->state() == QAbstractSocket::ConnectedState)
		m_descriptor = m_socket->socketDescriptor();

	connect(m_socket.get(), &QTcpSocket::disconnected,
			this, &CQuizClient::onSocketDisconnected);
}

/**
 * @brief	The slot should be called each time the \ref m_socket disconnects.
 */
void CQuizClient::onSocketDisconnected()
{
	qDebug() << "Client" << m_descriptor << "diconnected";
	emit disconnected(m_descriptor);
}























