#include "tcp_client.h"
#include "tcp_server.h"
#include "platform/common/socket_util.h"
#include <iostream>
#include <locale>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Portuguese");

    if (!SocketUtil::Initialize()) {
        std::cerr << "Erro ao inicializar o sistema de sockets." << std::endl;
        return -1;
    }

    if (argc > 1 && std::string(argv[1]) == "server") {
        int port = 8080;
        TCPServer server;
        if (server.start(port)) {
            std::cout << "Servidor iniciado na porta " << port << ". Aguardando conexões..." << std::endl;
        }
        else {
            std::cerr << "Falha ao iniciar o servidor." << std::endl;
            SocketUtil::Cleanup();
            return -1;
        }
    }
    else {
        TCPClient client;

        std::cout << "Entre com o endereço do servidor: ";
        std::string serverAddress;
        std::cin >> serverAddress;

        std::cout << "Entre com a porta do servidor: ";
        int port;
        std::cin >> port;

        if (client.connectToServer(serverAddress, port)) {
            std::cout << "Conectado ao servidor em " << serverAddress << ":" << port << std::endl;

            client.chatLoop();
        }
        else {
            std::cerr << "Falha ao conectar ao servidor." << std::endl;
        }
    }

    SocketUtil::Cleanup();
    return 0;
}
