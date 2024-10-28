#include "tcp_client.h"
#include "tcp_server.h"
#include "platform/common/socket_util.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (!SocketUtil::Initialize()) {
        std::cerr << "Erro ao inicializar o sistema de sockets." << std::endl;
        return -1;
    }

    if (argc > 1 && std::string(argv[1]) == "server") {
        int port = 8080;
        TCPServer server;
        if (server.start(port)) {
            std::cout << "Servidor iniciado na porta " << port << ". Aguardando conex�es..." << std::endl;
        }
        else {
            std::cerr << "Falha ao iniciar o servidor." << std::endl;
            SocketUtil::Cleanup();
            return -1;
        }
    }
    else {
        TCPClient client;
        std::cout << "Entre com o endere�o do servidor." << std::endl;
        std::string serverAddress;
        std::cin >> serverAddress;

        std::cout << "Entre com a porta do servidor." << std::endl;
        int port;
        std::cin >> port;

        if (client.connectToServer(serverAddress, port)) {
            std::cout << "Conectado ao servidor em " << serverAddress << ":" << port << std::endl;

            std::string message = "Ol�, servidor!";
            if (client.sendMessage(message)) {
                std::cout << "Mensagem enviada ao servidor: " << message << std::endl;
            }

            std::string response = client.receiveMessage();
            if (!response.empty()) {
                std::cout << "Resposta do servidor: " << response << std::endl;
            }

            client.disconnect();
        }
        else {
            std::cerr << "Falha ao conectar ao servidor." << std::endl;
        }
    }

    SocketUtil::Cleanup();
    return 0;
}
