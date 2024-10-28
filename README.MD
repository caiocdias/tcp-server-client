
# Projeto Cliente-Servidor TCP em C++

Este projeto é uma implementação de um sistema de cliente e servidor TCP em C++ usando sockets. Ele permite que o cliente se conecte ao servidor e troque mensagens interativas até que o usuário encerre a conexão.

## Estrutura do Projeto

```plaintext
.
??? CMakeLists.txt           # Arquivo de configuração do CMake
??? main.cpp                 # Arquivo principal que inicializa o cliente ou o servidor
??? src/
?   ??? tcp_client.cpp       # Implementação da classe TCPClient
?   ??? tcp_client.h         # Cabeçalho da classe TCPClient
?   ??? tcp_server.cpp       # Implementação da classe TCPServer
?   ??? tcp_server.h         # Cabeçalho da classe TCPServer
?   ??? platform/
?       ??? common/
?       ?   ??? socket_util.h  # Interface comum de funções de socket
?       ??? windows/
?       ?   ??? socket_util.cpp # Implementação de socket para Windows
?       ??? linux/
?           ??? socket_util.cpp # Implementação de socket para Linux
```

## Funcionalidades

- **Servidor TCP**: Escuta em uma porta especificada, aceita conexões de clientes e permite que o servidor envie mensagens para o cliente.
- **Cliente TCP**: Conecta-se ao servidor e entra em um loop interativo onde pode enviar e receber mensagens.
- **Comunicação Multiplataforma**: Implementação de sockets específica para Windows e Linux, facilitando a compatibilidade multiplataforma.

## Requisitos

- C++17 ou superior
- CMake 3.10 ou superior
- Biblioteca de Sockets (Winsock para Windows e POSIX para Linux)

## Compilação e Execução

### Compilar o Projeto

1. Clone o repositório:
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

Ao iniciar o cliente, ele solicitará o endereço IP do servidor e a porta para conectar.

## Como Usar

1. **Iniciar o Servidor**: Execute o servidor com o comando acima. O servidor ficará aguardando conexões de clientes.
2. **Iniciar o Cliente**: Execute o cliente e forneça o endereço e a porta do servidor para iniciar a comunicação.
3. **Interação Cliente-Servidor**: O cliente pode enviar mensagens digitando-as no terminal, e o servidor pode responder. A comunicação continua até que o cliente ou o servidor encerre a conexão.

## Exemplos de Comandos

- **Enviar mensagem do cliente ao servidor**: No cliente, digite uma mensagem e pressione `Enter` para enviá-la ao servidor.
- **Enviar resposta do servidor**: No servidor, digite uma resposta e pressione `Enter` para enviá-la ao cliente.

## Notas de Implementação

- A implementação utiliza threads para gerenciar as conexões e permitir comunicação contínua e simultânea entre o cliente e o servidor.
- As funções de sockets são abstraídas na `SocketUtil` para garantir que a implementação funcione tanto em Windows quanto em Linux.

## Estrutura do Código

- **main.cpp**: Ponto de entrada do programa. Inicializa o cliente ou servidor com base nos argumentos passados.
- **TCPClient**: Implementa a funcionalidade do cliente TCP, permitindo conexão, envio e recebimento de mensagens.
- **TCPServer**: Implementa a funcionalidade do servidor TCP, permitindo escutar uma porta, aceitar conexões e responder ao cliente.
- **SocketUtil**: Contém funções para operações de socket (conectar, enviar, receber, etc.) implementadas de forma específica para Windows e Linux.

## Contribuição

1. Faça um fork do projeto.
2. Crie uma branch para sua feature (`git checkout -b feature/NovaFeature`).
3. Commit suas mudanças (`git commit -m 'Adiciona NovaFeature'`).
4. Faça um push para a branch (`git push origin feature/NovaFeature`).
5. Abra um Pull Request.

## Licença

Este projeto é licenciado sob a licença MIT. Consulte o arquivo [LICENSE](LICENSE) para mais informações.
