#include "platform/common/socket_util.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib") // Linka a biblioteca Winsock

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
            std::cerr << "Erro ao criar o socket. Código de erro: " << WSAGetLastError() << std::endl;
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

    bool ListenSocket(int socket) {
        if (listen(socket, SOMAXCONN) == SOCKET_ERROR) {
            std::cerr << "Erro ao colocar em modo de escuta. Código de erro: " << WSAGetLastError() << std::endl;
            return false;
        }
        return true;
    }

    int AcceptConnection(int socket) {
        int clientSocket = accept(socket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Erro ao aceitar conexão. Código de erro: " << WSAGetLastError() << std::endl;
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

    bool SendData(int socket, const std::string& data) {
        int bytesSent = send(socket, data.c_str(), data.size(), 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "Erro ao enviar dados. Código de erro: " << WSAGetLastError() << std::endl;
            return false;
        }
        return true;
    }

    std::string ReceiveData(int socket) {
        char buffer[1024];
        int bytesReceived = recv(socket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
            std::cerr << "Erro ao receber dados ou conexão encerrada. Código de erro: " << WSAGetLastError() << std::endl;
            return "";
        }
        buffer[bytesReceived] = '\0';
        return std::string(buffer);
    }

    void CloseSocket(int socket) {
        closesocket(socket);
    }
}
