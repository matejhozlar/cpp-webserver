#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include <winsock2.h>

class Router {
public:
    using RouteHandler = std::function<void(SOCKET)>;

    void addRoute(const std::string& path, RouteHandler handler);
    bool routeExists(const std::string& path) const;
    void handle(const std::string& path, SOCKET client_socket) const;

private:
    std::unordered_map<std::string, RouteHandler> routes;
};

#endif
