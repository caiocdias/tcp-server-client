#include "tcp_client.h"
#include "tcp_server.h"
#include "platform/common/socket_util.h"
#include <iostream>

int main(int argc, char* agrv[]) {
	if (!SocketUtil::Initialize()) {
		std::cerr << "Erro ao inicializar sistema de sockets." << std::endl;
		return -1;
	}

	if (argc > 1 && std::string(argv[1]) == "server") {
		TCPServer server;
		server.start();
	}
	else {
		TCPClient client;
		client.connect("127.0.0.1", 8080);
	}

	SocketUtil::Cleanup();
	return 0;
}