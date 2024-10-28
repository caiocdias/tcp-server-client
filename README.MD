
# Projeto Cliente-Servidor TCP em C++

Este projeto � uma implementa��o de um sistema de cliente e servidor TCP em C++ usando sockets. Ele permite que o cliente se conecte ao servidor e troque mensagens interativas at� que o usu�rio encerre a conex�o.

## Estrutura do Projeto

```plaintext
.
??? CMakeLists.txt           # Arquivo de configura��o do CMake
??? main.cpp                 # Arquivo principal que inicializa o cliente ou o servidor
??? src/
?   ??? tcp_client.cpp       # Implementa��o da classe TCPClient
?   ??? tcp_client.h         # Cabe�alho da classe TCPClient
?   ??? tcp_server.cpp       # Implementa��o da classe TCPServer
?   ??? tcp_server.h         # Cabe�alho da classe TCPServer
?   ??? platform/
?       ??? common/
?       ?   ??? socket_util.h  # Interface comum de fun��es de socket
?       ??? windows/
?       ?   ??? socket_util.cpp # Implementa��o de socket para Windows
?       ??? linux/
?           ??? socket_util.cpp # Implementa��o de socket para Linux
```

## Funcionalidades

- **Servidor TCP**: Escuta em uma porta especificada, aceita conex�es de clientes e permite que o servidor envie mensagens para o cliente.
- **Cliente TCP**: Conecta-se ao servidor e entra em um loop interativo onde pode enviar e receber mensagens.
- **Comunica��o Multiplataforma**: Implementa��o de sockets espec�fica para Windows e Linux, facilitando a compatibilidade multiplataforma.

## Requisitos

- C++17 ou superior
- CMake 3.10 ou superior
- Biblioteca de Sockets (Winsock para Windows e POSIX para Linux)

## Compila��o e Execu��o

### Compilar o Projeto

1. Clone o reposit�rio:
   ```bash
   git clone <link-do-repositorio>
   cd <nome-do-repositorio>
   ```

2. Compile o projeto com CMake:
   ```bash
   cmake -S . -B build
   cmake --build build
   ```

### Executar o Servidor

Para iniciar o servidor:
```bash
./build/tcp_project server
```

### Executar o Cliente

Para iniciar o cliente:
```bash
./build/tcp_project
```

Ao iniciar o cliente, ele solicitar� o endere�o IP do servidor e a porta para conectar.

## Como Usar

1. **Iniciar o Servidor**: Execute o servidor com o comando acima. O servidor ficar� aguardando conex�es de clientes.
2. **Iniciar o Cliente**: Execute o cliente e forne�a o endere�o e a porta do servidor para iniciar a comunica��o.
3. **Intera��o Cliente-Servidor**: O cliente pode enviar mensagens digitando-as no terminal, e o servidor pode responder. A comunica��o continua at� que o cliente ou o servidor encerre a conex�o.

## Exemplos de Comandos

- **Enviar mensagem do cliente ao servidor**: No cliente, digite uma mensagem e pressione `Enter` para envi�-la ao servidor.
- **Enviar resposta do servidor**: No servidor, digite uma resposta e pressione `Enter` para envi�-la ao cliente.

## Notas de Implementa��o

- A implementa��o utiliza threads para gerenciar as conex�es e permitir comunica��o cont�nua e simult�nea entre o cliente e o servidor.
- As fun��es de sockets s�o abstra�das na `SocketUtil` para garantir que a implementa��o funcione tanto em Windows quanto em Linux.

## Estrutura do C�digo

- **main.cpp**: Ponto de entrada do programa. Inicializa o cliente ou servidor com base nos argumentos passados.
- **TCPClient**: Implementa a funcionalidade do cliente TCP, permitindo conex�o, envio e recebimento de mensagens.
- **TCPServer**: Implementa a funcionalidade do servidor TCP, permitindo escutar uma porta, aceitar conex�es e responder ao cliente.
- **SocketUtil**: Cont�m fun��es para opera��es de socket (conectar, enviar, receber, etc.) implementadas de forma espec�fica para Windows e Linux.

## Contribui��o

1. Fa�a um fork do projeto.
2. Crie uma branch para sua feature (`git checkout -b feature/NovaFeature`).
3. Commit suas mudan�as (`git commit -m 'Adiciona NovaFeature'`).
4. Fa�a um push para a branch (`git push origin feature/NovaFeature`).
5. Abra um Pull Request.

## Licen�a

Este projeto � licenciado sob a licen�a MIT. Consulte o arquivo [LICENSE](LICENSE) para mais informa��es.