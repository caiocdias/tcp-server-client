#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <string>

class TCPClient {
public:
	TCPClient();
	~TCPClient();

	bool connectToServer(const std::string& address, int port);
	void disconnect();
	bool sendMessage(const std::string& message);
	void chatLoop();
	std::string receiveMessage();

private:
	int clientSocket;
	bool isConnected;

};

#endif //TCP_CLIENT_H