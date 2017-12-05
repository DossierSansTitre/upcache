#include <netinet/ip.h>
#include <stdio.h>
#include <private/upcached.h>

void upcached_server_init(upcached_server* server)
{
    uv_loop_init(&server->event_loop);
    server->event_loop.data = server;
    uv_tcp_init(&server->event_loop, &server->socket);
    uv_tcp_init(&server->event_loop, &server->socket6);
}

static void connection_cb(uv_stream_t* socket, int status)
{
    printf("EVENT\n");
}

void upcached_server_run(upcached_server* server)
{
    struct sockaddr_in addr;
    struct sockaddr_in6 addr6;

    uv_ip4_addr("0.0.0.0", 8075, &addr);
    uv_ip6_addr("::", 8075, &addr6);

    uv_tcp_bind(&server->socket, (struct sockaddr*)&addr, 0);
    uv_tcp_bind(&server->socket6, (struct sockaddr*)&addr6, UV_TCP_IPV6ONLY);

    uv_listen((uv_stream_t*)&server->socket, 64, &connection_cb);
    uv_listen((uv_stream_t*)&server->socket6, 64, &connection_cb);

    printf("Server started on tcp://localhost:8075\n");
    uv_run(&server->event_loop, 0);
}
