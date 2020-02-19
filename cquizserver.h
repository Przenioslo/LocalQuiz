#ifndef CQUIZSERVER_H
#define CQUIZSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QSet>
#include <QPair>
#include <memory>

#include "cquizclient.h"

/**
 * @brief	A shared pointer for the tcp socket type
 */
using ClientPtr = std::shared_ptr<CQuizClient>;

/**
 * @brief	A type specifying a list of TCP socket connections
 */
using ClientList = QList<ClientPtr>;

/**
 * @brief	A class providing the quiz hosting interface
 */
class CQuizServer : public QObject
{
	Q_OBJECT

public:

	explicit CQuizServer(const int port = 12345,
						 const bool sStart = true,
						 QObject *parent = nullptr);
	~CQuizServer();

	int start();
	void stop();
	int port();
	int setPort(const int port);

private slots:

	void onNewConnections();
	void onClientDisconnected(const qintptr desc);

private:

	ClientPtr makeNextClient(SocketPtr socket);
	void removeDeadClients();

	/**
	 * @brief	The Quiz host server
	 */
	QTcpServer m_server;

	/**
	 * @brief	A list of connected Quiz clients
	 */
	ClientList m_clients;

	/**
	 * @brief	The listening port.
	 */
	int m_port;

};

#endif // CQUIZSERVER_H
