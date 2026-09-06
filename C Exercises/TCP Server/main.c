#include "tcp_server.h"

#define handler() handler_
PRIVATE void handler_(connection_t *conn) { return; }

int main() {
    server_t *server;

    server = tcp_server(8585, handler());
    if (server && !server->ok()) {
        printf("Error: %s\n", server->err());
        return -1;
    }

    printf("Listening to the port %d\n", 8585);
    return server->listen();
}
