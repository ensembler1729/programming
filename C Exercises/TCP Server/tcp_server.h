#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define PUBLIC __attribute__((visibility("default")))
#define PRIVATE __attribute__((visibility("hidden"))) static
#define INIT __attribute__((constructor))
#define CLOSE __attribute__((destructor))

typedef struct connection_s connection_t;
typedef struct server_s server_t;
typedef void (*callback)(connection_t *);

enum { ERR, OK };

// x is (char *)
#define server_err(x)                                                          \
    do {                                                                       \
        server_t *_srv;                                                        \
        _srv = (server_t *)malloc(sizeof(*_srv));                              \
        assert(_srv);                                                          \
        _srv->fd = 0;                                                          \
        _srv->status = ERR;                                                    \
        memcpy((char *)_srv->errmsg, (char *)(x), strlen((char *)(x)));        \
        return _srv;                                                           \
    } while (true)

struct connection_s {
    u32 fd;
    char host[16];
    u16 port;
};
struct server_s {
    u32 fd;
    u16 port;
    u8 status : 1;
    char *errmsg;

    bool (*ok)();
    char *(*err)();
    callback cb;
    i32 (*listen)();
};

int main(void);
PRIVATE void start(void);
PUBLIC server_t *tcp_server(u16, callback);
PRIVATE bool server_ok();
PRIVATE char *server_errormsg();
PRIVATE i32 server_listen();

#endif
