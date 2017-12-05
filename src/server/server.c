#include <netinet/ip.h>
#include <stdio.h>
#include <private/upcached.h>

static int create_socket6()
{
    int sd;
    int v6only;
    struct sockaddr_in6 addr;

    v6only = 0;
    sd = socket(PF_INET6, SOCK_STREAM, 0);
    setsockopt(sd, IPPROTO_IPV6, IPV6_V6ONLY, &v6only, sizeof(v6only));
    memset(&addr, 0, sizeof(addr));
    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(8075);
    addr.sin6_addr = in6addr_any;
    bind(sd, (struct sockaddr*)&addr, sizeof(addr));
    return sd;
}

static int create_socket()
{
    int sd;
    struct sockaddr_in addr;

    sd = socket(PF_INET, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8075);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sd, (struct sockaddr*)&addr, sizeof(addr));
    return sd;
}

void upcached_server_init(upcached_server* server)
{
    server->event_loop = EV_DEFAULT;
}

static void socket_cb(struct ev_loop* event_loop, ev_io* watcher, int revents)
{
    printf("SOCKET EVENT");
}

void upcached_server_run(upcached_server* server)
{
    struct ev_loop* loop;

    loop = server->event_loop;
    server->socket = create_socket();
    server->socket6 = create_socket6();
    listen(server->socket, 64);
    listen(server->socket6, 64);
    ev_io_init(&server->socket_watcher, &socket_cb, server->socket, EV_READ);
    ev_io_init(&server->socket_watcher6, &socket_cb, server->socket6, EV_READ);
    server->socket_watcher.data = server;
    server->socket_watcher6.data = server;
    ev_io_start(EV_A_ &server->socket_watcher);
    ev_io_start(EV_A_ &server->socket_watcher6);
    printf("Server started on tcp://localhost:8075\n");
    ev_run(server->event_loop, 0);
}
