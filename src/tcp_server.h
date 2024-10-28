#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <string>

class TCPServer {
public:
	TCPServer();
	~TCPServer();

	bool start(int port);
	void stop();
	void acceptConnections();

private:
	int serverSocket;
	bool isRunning;

	void handleClient(int clientSocket);
	bool createSocket();
	bool bindSocket(int port);
	bool listenSocket();
};
#endif // TCP_SERVER_H