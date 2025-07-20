#include "router.hpp"
#include <iostream>

void Router::addRoute(const std::string& path, RouteHandler handler) {
    routes[path] = handler;
}

bool Router::routeExists(const std::string& path) const {
    return routes.find(path) != routes.end();
}

void Router::handle(const std::string& path, SOCKET client_socket) const {
    auto it = routes.find(path);
    if (it != routes.end()) {
        it->second(client_socket);
    }
}