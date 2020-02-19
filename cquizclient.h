#ifndef CQUIZCLIENT_H
#define CQUIZCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <memory>

/**
 * @brief	A TCP socket smart pointer type
 */
using SocketPtr = std::shared_ptr<QTcpSocket>;

/**
 * @brief	A client interface class
 */
class CQuizClient : public QObject
{
	Q_OBJECT

public:

	explicit CQuizClient(SocketPtr socket, QObject *parent = nullptr);
	~CQuizClient();

	qintptr descriptor();
	void disconnect();
	bool socketConnected();
	void assignSocket(SocketPtr socket);

signals:

	void disconnected(const qintptr desc);

private slots:

	void onSocketDisconnected();

private:

	//socketPtr nextDisconnectedClient();

	/**
	 * @brief	The server connection socket
	 */
	SocketPtr m_socket;

	/**
	 * @brief	The client socket last connection descriptor
	 */
	qintptr m_descriptor = 0;

};

#endif // CQUIZCLIENT_H
