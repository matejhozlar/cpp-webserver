#include "server.hpp"

int main() {
    Server server(8080);
    if (!server.start()) {
        return 1;
    }
    return 0;
}
