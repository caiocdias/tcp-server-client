#include "tcp_client.h"
#include "platform/common/socket_util.h"
#include <iostream>
#include <string>
#include <thread>
#include <atomic>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

TCPClient::TCPClient() : clientSocket(-1), isConnected(false) {
}

TCPClient::~TCPClient() {
    disconnect();
}

bool TCPClient::connectToServer(const std::string& address, int port) {
    clientSocket = SocketUtil::CreateSocket();
    if (clientSocket == -1) {
        std::cerr << "Erro ao criar socket do cliente." << std::endl;
        return false;
    }

    if (!SocketUtil::ConnectSocket(clientSocket, address.c_str(), port)) {
        std::cerr << "Erro ao conectar ao servidor." << std::endl;
        SocketUtil::CloseSocket(clientSocket);
        return false;
    }

    isConnected = true;
    std::cout << "Conectado ao servidor " << address << " na porta " << port << std::endl;
    return true;
}

void TCPClient::disconnect() {
    if (isConnected) {
        SocketUtil::CloseSocket(clientSocket);
        isConnected = false;
        std::cout << "Desconectado do servidor." << std::endl;
    }
}

bool TCPClient::sendMessage(const std::string& message) {
    if (!isConnected) {
        std::cerr << "Cliente não está conectado." << std::endl;
        return false;
    }

    int bytesSent = send(clientSocket, message.c_str(), message.size(), 0);
    if (bytesSent == -1) {
        std::cerr << "Erro ao enviar mensagem." << std::endl;
        return false;
    }

    std::cout << "Mensagem enviada: " << message << std::endl;
    return true;
}

std::string TCPClient::receiveMessage() {
    if (!isConnected) {
        std::cerr << "Cliente não está conectado." << std::endl;
        return "";
    }

    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytesReceived <= 0) {
        std::cerr << "Erro ao receber mensagem ou conexão fechada." << std::endl;
        return "";
    }

    buffer[bytesReceived] = '\0';
    return std::string(buffer);
}

void TCPClient::chatLoop() {
    std::atomic<bool> running(true);

    std::thread receiveThread([&]() {
        while (running && isConnected) {
            std::string receivedMessage = receiveMessage();
            if (receivedMessage.empty()) {
                running = false;
                break;
            }
            std::cout << "\nServidor: " << receivedMessage << "\nDigite uma mensagem: ";
            std::cout.flush();
        }
        });

    while (running && isConnected) {
        std::cout << "Digite uma mensagem: ";
        std::string message;
        std::getline(std::cin, message);

        if (message == "exit") {
            running = false;
            break;
        }

        if (!sendMessage(message)) {
            std::cerr << "Erro ao enviar mensagem. Encerrando..." << std::endl;
            running = false;
            break;
        }
    }

    running = false;
    if (receiveThread.joinable()) {
        receiveThread.join();
    }

    disconnect();
}
