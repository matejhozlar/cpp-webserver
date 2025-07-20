#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

int main () {
    WSADATA wsaData;

    int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaResult != 0) {
        std::cerr << "WSAStartup failed: " << wsaResult << std::endl;
        return false;
    }

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        return false;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed.\n";
        closesocket(server_socket);
        WSACleanup();
        return false;
    }

    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed.\n";
        closesocket(server_socket);
        WSACleanup();
        return false;
    }

    std::cout << "Listening on port 8080...\n";

    SOCKET client_socket;
    sockaddr client_socket;
    sockaddr_in client_addr;
    int client_size = sizeof(client_addr);

    while ((client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_size)) != INVALID_SOCKET) {
        const char* http_response =
        "HTTP/1.1 200 OK\r\n"
        "Content_Type: text/html\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<html><body><h1>Hello World!</h1></body></html>";

        send(client_socket, http_response, strlen(http_response), 0);
        closesocket(client_socket);
    }

    closesocket(server_socket);
    WSACleanup();
    return true;
}

