#include "platform/common/socket_util.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

namespace SocketUtil {
	bool Initialize() {
		WSADATA wsaData;
		return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
	}

	void Cleanup() {
		WSACleanup();
	}

	int CreateSocket() {
		int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sock == INVALID_SOCKET) {
			std::cerr << "Erro ao criar socket. Código de erro: " << WSAGetLastError() << std::endl;
			return -1;
		}
		return sock;
	}

	bool BindSocket(int socket, int port) {
		sockaddr_in serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = INADDR_ANY;
		serverAddr.sin_port = htons(port);

		if (bind(socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
			std::cerr << "Erro ao fazer bind. Código de erro: " << WSAGetLastError() << std::endl;
			return false;
		}

		return true;
	}

	int AcceptConnection(int socket) {
		int clientSocket = accept(socket, nullptr, nullptr);
		if (clientSocket == INVALID_SOCKET) {
			std::cerr << "Erro ao aceitar a conexão. Código de erro: " << WSAGetLastError() << std::endl;
			return -1;
		}
		return clientSocket;
	}

	bool ConnectSocket(int socket, const char* address, int port) {
		sockaddr_in serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(port);
		inet_pton(AF_INET, address, &serverAddr.sin_addr);

		if (connect(socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
			std::cerr << "Erro ao conectar ao servidor. Código de erro: " << WSAGetLastError() << std::endl;
			return false;
		}
		return true;
	}

	void CloseSocket(int socket) {
		closesocket(socket);
	}
}