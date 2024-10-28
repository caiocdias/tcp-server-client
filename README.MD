
# TCP Client-Server Project in C++

This project is an implementation of a TCP client-server system in C++ using sockets. It allows the client to connect to the server and exchange interactive messages until the user ends the connection.

## Features

- **TCP Server**: Listens on a specified port, accepts client connections, and allows the server to send messages to the client.
- **TCP Client**: Connects to the server and enters an interactive loop where it can send and receive messages.
- **Cross-Platform Communication**: Platform-specific socket implementations for Windows and Linux, ensuring cross-platform compatibility.

## Requirements

- C++17 or higher
- CMake 3.10 or higher
- Sockets library (Winsock for Windows and POSIX for Linux)

## Compilation and Execution

### Compiling the Project

1. Clone the repository:
   ```bash
   git clone <repository-link>
   cd <repository-name>
   ```

2. Build the project with CMake:
   ```bash
   cmake -S . -B build
   cmake --build build
   ```

### Running the Server

To start the server:
```bash
./build/tcp_project server
```

### Running the Client

To start the client:
```bash
./build/tcp_project
```

When starting the client, it will prompt for the server's IP address and port to connect.

## Usage

1. **Starting the Server**: Run the server using the command above. The server will wait for client connections.
2. **Starting the Client**: Run the client and provide the server's address and port to initiate communication.
3. **Client-Server Interaction**: The client can send messages by typing them in the terminal, and the server can respond. Communication continues until either the client or the server closes the connection.

## Command Examples

- **Send a message from client to server**: On the client, type a message and press `Enter` to send it to the server.
- **Send a response from server to client**: On the server, type a response and press `Enter` to send it to the client.

## Implementation Notes

- The implementation uses threads to manage connections and enable continuous, simultaneous communication between the client and server.
- Socket functions are abstracted in `SocketUtil` to ensure the implementation works on both Windows and Linux.

## Code Structure

- **main.cpp**: The program's entry point. Initializes the client or server based on the provided arguments.
- **TCPClient**: Implements the client TCP functionality, enabling connection, sending, and receiving messages.
- **TCPServer**: Implements the server TCP functionality, allowing it to listen on a port, accept connections, and respond to the client.
- **SocketUtil**: Contains functions for socket operations (connect, send, receive, etc.) with platform-specific implementations for Windows and Linux.

## Contribution

1. Fork the project.
2. Create a branch for your feature (`git checkout -b feature/NewFeature`).
3. Commit your changes (`git commit -m 'Add NewFeature'`).
4. Push to the branch (`git push origin feature/NewFeature`).
5. Open a Pull Request.

## License

This project is licensed under the MIT license. See the [LICENSE](LICENSE) file for more information.
