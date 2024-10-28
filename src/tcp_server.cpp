#include "tcp_server.h"
#include "platform/common/socket_util.h"
#include <iostream>

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

	if (!bindSocket()) {
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
			// Aqui adicionar lógica para lidar com o cliente, como leitura/escrita
			SocketUtil::CloseSocket(clientSocket);
		}
	}
}