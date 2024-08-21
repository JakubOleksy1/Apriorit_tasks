#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

DWORD WINAPI handle_client(LPVOID client_socket) {
    SOCKET client = *(SOCKET*)client_socket;
    char buffer[BUFFER_SIZE];
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(client, buffer, BUFFER_SIZE, 0);
        if (bytes_received == SOCKET_ERROR) {
            std::cerr << "Error reading from socket: " << WSAGetLastError() << std::endl;
            break;
        } else if (bytes_received == 0) {
            std::cout << "Client disconnected" << std::endl;
            break;
        }

        std::string message(buffer);
        if (message == "hello") {
            std::string response = "world";
            send(client, response.c_str(), response.size(), 0);
        } else if (message == "disconnect") {
            std::cout << "Client requested disconnect" << std::endl;
            break;
        } else {
            send(client, buffer, bytes_received, 0);
        }
    }
    closesocket(client);
    return 0;
}

int main() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return EXIT_FAILURE;
    }

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return EXIT_FAILURE;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    result = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (result == SOCKET_ERROR) {
        std::cerr << "Error binding socket: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return EXIT_FAILURE;
    }

    result = listen(server_socket, 10);
    if (result == SOCKET_ERROR) {
        std::cerr << "Error listening on socket: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return EXIT_FAILURE;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        struct sockaddr_in client_addr;
        int client_len = sizeof(client_addr);
        SOCKET client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == INVALID_SOCKET) {
            std::cerr << "Error accepting connection: " << WSAGetLastError() << std::endl;
            continue;
        }

        std::cout << "Client connected" << std::endl;

        HANDLE thread = CreateThread(NULL, 0, handle_client, &client_socket, 0, NULL);
        if (thread == NULL) {
            std::cerr << "Error creating thread: " << GetLastError() << std::endl;
            closesocket(client_socket);
        } else {
            CloseHandle(thread);
        }
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}