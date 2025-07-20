#ifndef SERVER_HPP
#define SERVER_HPP

#include "router.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

class Server {
public:
    Server(int port);
    ~Server();

    bool start();
    void stop();

private:
    int port;
    SOCKET server_socket;
    bool running;

    Router router;
    void handleClient(SOCKET client_socket);
    void registerRoutes();
};

#endif
