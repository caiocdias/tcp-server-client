#include "tcp_server.h"
#include "platform/common/socket_util.h"
#include <iostream>
#include <string>
#include <thread>

TCPServer::TCPServer() : serverSocket(-1), isRunning(false) {
}

TCPServer::~TCPServer() {
    stop();
}

bool TCPServer::start(int port) {
    if (!createSocket()) {
        std::cerr << "Erro ao criar socket do servidor." << std::endl;
        return false;
    }

    if (!bindSocket(port)) {
        std::cerr << "Erro ao fazer bind na porta: " << port << std::endl;
        return false;
    }

    if (!listenSocket()) {
        std::cerr << "Erro ao colocar o servidor em modo de escuta." << std::endl;
        return false;
    }

    isRunning = true;
    std::cout << "Servidor iniciado e escutando na porta " << port << std::endl;

    acceptConnections();
    return true;
}

void TCPServer::stop() {
    if (isRunning) {
        SocketUtil::CloseSocket(serverSocket);
        isRunning = false;
        std::cout << "Servidor parado." << std::endl;
    }
}

bool TCPServer::createSocket() {
    serverSocket = SocketUtil::CreateSocket();
    return serverSocket != -1;
}

bool TCPServer::bindSocket(int port) {
    return SocketUtil::BindSocket(serverSocket, port);
}

bool TCPServer::listenSocket() {
    return SocketUtil::ListenSocket(serverSocket);
}

void TCPServer::acceptConnections() {
    while (isRunning) {
        int clientSocket = SocketUtil::AcceptConnection(serverSocket);
        if (clientSocket != -1) {
            std::cout << "Cliente conectado!" << std::endl;
            handleClient(clientSocket);
        }
    }
}

void TCPServer::handleClient(int clientSocket) {
    std::thread clientThread([this, clientSocket]() {
        bool connected = true;

        while (connected) {
            std::string message = SocketUtil::ReceiveData(clientSocket);
            if (message.empty()) {
                std::cout << "Conexão com o cliente encerrada." << std::endl;
                connected = false;
                break;
            }

            std::cout << "Mensagem do cliente: " << message << std::endl;

            std::cout << "Digite uma mensagem para o cliente: ";
            std::string response;
            std::getline(std::cin, response);

            if (!SocketUtil::SendData(clientSocket, response)) {
                std::cerr << "Erro ao enviar mensagem para o cliente." << std::endl;
                connected = false;
            }
        }

        SocketUtil::CloseSocket(clientSocket);
        });

    clientThread.detach();
}
