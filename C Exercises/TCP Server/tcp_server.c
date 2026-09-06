#include "tcp_server.h"

PUBLIC server_t *__GLOBAL_SERVER__;

PRIVATE INIT void intialize() {
    __GLOBAL_SERVER__ = (server_t *)0;
    return;
}

PUBLIC server_t *tcp_server(u16 port, callback cb) {
    i32 ret;
    u32 server_fd;
    struct sockaddr_in sock;

    if (__GLOBAL_SERVER__)
        server_err("TCP Server already initialized.");

    ret = socket(AF_INET, SOCK_STREAM, 0); // TCP over IPv4
    if (ret < 0)
        server_err("Failed to initialize socket.");
    else
        server_fd = ret;

    struct sockaddr_in sock_addr;
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr = INADDR_ANY; // bind to all interfaces

    ret = bind(server_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
    if (ret < 0) {
        close(server_fd);
        server_err("Failed to bind the socket to the port.");
    }

    ret = listen(server_fd, 10);
    if (ret < 0) {
        close(server_fd);
        server_err("Failed to listen to the port.");
    }

    server_t *server = malloc(sizeof(*server));
    assert(server);
    server->fd = server_fd;
    server->port = port;
    server->status = OK;
    server->errmsg = NULL;
    server->ok = &server_ok;
    server->err = &server_errormsg;
    server->listen = &server_listen;
    server->cb = cb;
    __GLOBAL_SERVER__ = server;
    return server;
}

PRIVATE bool server_ok() {
    if (!__GLOBAL_SERVER__)
        return false;
    return (__GLOBAL_SERVER__->status == OK) ? true : false;
}

PRIVATE char *server_errormsg() {
    if (!__GLOBAL_SERVER__)
        return "TCP Server not initialized";
    else if (__GLOBAL_SERVER__->status != ERR)
        return "NO ERROR";
    else
        return __GLOBAL_SERVER__->errmsg;
}

PRIVATE i32 server_listen() {
    i32 ret;
    u32 client_fd;
    struct sockaddr_in sock;
    socklen_t sock_len = sizeof(struct sockaddr_in);
    socklen_t *socklen_ptr = &sock_len;

    if (!__GLOBAL_SERVER__)
        return -1;
    else if (__GLOBAL_SERVER__->status == ERR)
        return -1;

    if (!fork())
        exit(0);

    // Child Process
    while (true) {
        ret =
            accept(__GLOBAL_SERVER__->fd, (struct sockaddr *)&sock, &sock_len);
        if (ret < 0) {
            sleep(2);
            continue;
        } else
            client_fd = ret;

        connection_t *conn = malloc(sizeof(*conn));
        if (!conn) {
            close(ret);
            sleep(2);
            continue;
        }
        conn->fd = client_fd;
        inet_ntop(AF_INET, &sock.sin_addr, conn->host, sizeof(conn->host));
        conn->port = ntohs(sock.sin_port);
        if (!fork()) {
            if (conn)
                free(conn);
            continue;
        }

        // Child Process
        __GLOBAL_SERVER__->cb(conn);
        exit(0);
    }
    exit(0);
    return 0;
}
