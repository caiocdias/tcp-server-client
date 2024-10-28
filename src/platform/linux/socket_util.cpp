#include "platform/common/socket_util.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

namespace SocketUtil {
    bool Initialize() {
        // No Linux, não precisamos de inicialização especial
        return true;
    }

    void Cleanup() {
        // No Linux, não precisamos de uma limpeza especial
    }

    int CreateSocket() {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            std::cerr << "Erro ao criar o socket." << std::endl;
        }
        return sock;
    }

    bool BindSocket(int socket, int port) {
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);

        if (bind(socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
            std::cerr << "Erro ao fazer bind." << std::endl;
            return false;
        }
        return true;
    }

    bool ListenSocket(int socket) {
        if (listen(socket, SOMAXCONN) == -1) {
            std::cerr << "Erro ao colocar em modo de escuta." << std::endl;
            return false;
        }
        return true;
    }

    int AcceptConnection(int socket) {
        int clientSocket = accept(socket, nullptr, nullptr);
        if (clientSocket == -1) {
            std::cerr << "Erro ao aceitar conexão." << std::endl;
        }
        return clientSocket;
    }

    bool ConnectSocket(int socket, const char* address, int port) {
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        inet_pton(AF_INET, address, &serverAddr.sin_addr);

        if (connect(socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
            std::cerr << "Erro ao conectar ao servidor." << std::endl;
            return false;
        }
        return true;
    }

    void CloseSocket(int socket) {
        close(socket);
    }
}