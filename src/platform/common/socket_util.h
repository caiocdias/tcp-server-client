#ifndef SOCKET_UTIL_H
#define SOCKET_UTIL_H

#include <string>

namespace SocketUtil {
    bool Initialize();           // Inicializa o sistema de sockets
    void Cleanup();              // Finaliza o sistema de sockets
    int CreateSocket();          // Cria um socket
    bool BindSocket(int socket, int port); // Faz o bind do socket à porta
    bool ListenSocket(int socket);         // Coloca o socket em modo de escuta
    int AcceptConnection(int socket);      // Aceita conexões de clientes
    bool ConnectSocket(int socket, const char* address, int port); // Conecta ao servidor
    bool SendData(int socket, const std::string& data); // Envia dados para o servidor
    std::string ReceiveData(int socket); // Recebe dados do servidor
    void CloseSocket(int socket);        // Fecha o socket
}

#endif // SOCKET_UTIL_H
