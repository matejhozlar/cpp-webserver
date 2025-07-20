#include "server.hpp"
#include "logger.hpp"

int main() {
    Logger::init();

    Logger::info("Starting the server...");
    Server server(8080);

    if (!server.start()) {
        Logger::error("Failed to start the server");
        return 1;
    }

    return 0;
}
