#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return EXIT_FAILURE;
    }

    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return EXIT_FAILURE;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    server_addr.sin_port = htons(PORT);

    result = connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (result == SOCKET_ERROR) {
        std::cerr << "Error connecting to server: " << WSAGetLastError() << std::endl;
        closesocket(client_socket);
        WSACleanup();
        return EXIT_FAILURE;
    }

    std::cout << "Connected to server" << std::endl;

    char buffer[BUFFER_SIZE];
    while (true) {
        std::cout << "Enter message: ";
        std::string message;
        std::getline(std::cin, message);

        if (message == "disconnect") {
            send(client_socket, message.c_str(), message.size(), 0);
            break;
        }

        send(client_socket, message.c_str(), message.size(), 0);

        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received == SOCKET_ERROR) {
            std::cerr << "Error reading from socket: " << WSAGetLastError() << std::endl;
            break;
        }

        std::cout << "Server response: " << buffer << std::endl;
    }

    closesocket(client_socket);
    WSACleanup();
    return 0;
}