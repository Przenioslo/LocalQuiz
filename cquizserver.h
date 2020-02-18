#ifndef CQUIZSERVER_H
#define CQUIZSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSet>
#include <QPair>
#include <memory>

/**
 * @brief	A shared pointer for the tcp socket type
 */
using socketPtr = std::shared_ptr<QTcpSocket>;

/**
 * @brief	A single socket descriptor
 */
using socketObj = QPair<std::shared_ptr<QTcpSocket>, qintptr>;

/**
 * @brief	A type specifying a list of TCP socket connections
 */
using SocketList = QList<socketObj>;

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
	void onClientDisconnected();

private:

	/**
	 * @brief	The Quiz host server
	 */
	QTcpServer m_server;

	/**
	 * @brief	A list of connected Quiz clients
	 */
	SocketList m_clients;

	/**
	 * @brief	The listening port.
	 */
	int m_port;

};

#endif // CQUIZSERVER_H
