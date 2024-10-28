#ifndef SOCKET_UTIL_H

#define SOCKET_UTIL_H

namespace SocketUtil {
	bool Initialize();
	void Cleanup();
	int CreateSocket();
	bool BindSocket(int socket, int port);
	bool ListenSocket(int socket);
	int AcceptConnection(int socket);
	void CloseSocket(int socket);
}


#endif // SOCKET_UTIL_H