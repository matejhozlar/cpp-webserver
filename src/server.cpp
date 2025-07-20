#include "server.hpp"
#include <iostream>
#include <ws2tcpip.h>
#include <fstream>
#include <sstream>
#include <filesystem>

#pragma comment(lib, "ws2_32.lib")

Server::Server(int port) : port(port), server_socket(INVALID_SOCKET), running(false) {}

Server::~Server() {
    stop();
}

bool Server::start() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return false;
    }

    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        return false;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed.\n";
        stop();
        return false;
    }

    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed.\n";
        stop();
        return false;
    }

    std::cout << "Listening on port " << port << "...\n";
    running = true;

    while (running) {
        sockaddr_in client_addr;
        int client_size = sizeof(client_addr);
        SOCKET client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_size);

        if (client_socket != INVALID_SOCKET) {
            handleClient(client_socket);
        }
    }

    return true;
}

void Server::handleClient(SOCKET client_socket) {
    char buffer[1024];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received <= 0) {
        closesocket(client_socket);
        return;
    }
    buffer[bytes_received] = '\0';

    std::istringstream request_stream(buffer);
    std::string method, path, version;
    request_stream >> method >> path >> version;

    // Only handle GET
    if (method != "GET") {
        closesocket(client_socket);
        return;
    }

    if (path == "/") {
        path = "/index.html";
    }

    std::string full_path = "./public" + path;

    std::ifstream file(full_path, std::ios::binary);
    if (!file.is_open()) {
        std::string not_found =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "404 Not Found";
        send(client_socket, not_found.c_str(), not_found.size(), 0);
        closesocket(client_socket);
        return;
    }

    std::ostringstream content_stream;
    content_stream << file.rdbuf();
    std::string content = content_stream.str();

    std::string content_type = "text/plain";
    if (path.ends_with(".html")) content_type = "text/html";
    else if (path.ends_with(".css")) content_type = "text/css";
    else if (path.ends_with(".js")) content_type = "application/javascript";
    else if (path.ends_with(".png")) content_type = "image/png";
    else if (path.ends_with(".jpg") || path.ends_with(".jpeg")) content_type = "image/jpeg";
    else if (path.ends_with(".svg")) content_type = "image/svg+xml";

std::ostringstream response;
response << "HTTP/1.1 200 OK\r\n"
         << "Content-Type: " << content_type << "\r\n"
         << "Content-Length: " << content.size() << "\r\n"
         << "Connection: close\r\n\r\n"
         << content;

    std::string response_str = response.str();
    send(client_socket, response_str.c_str(), response_str.size(), 0);
    closesocket(client_socket);
}

void Server::stop() {
    running = false;
    if (server_socket != INVALID_SOCKET) {
        closesocket(server_socket);
        server_socket = INVALID_SOCKET;
    }
    WSACleanup();
}
