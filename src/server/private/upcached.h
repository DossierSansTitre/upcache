#ifndef INCLUDED_PRIVATE_UPCACHED_H
#define INCLUDED_PRIVATE_UPCACHED_H

#include <uv.h>

struct upcached_server_
{
    uv_loop_t event_loop;
    uv_tcp_t socket;
    uv_tcp_t socket6;
};

typedef struct upcached_server_ upcached_server;

/* server.c */
void upcached_server_init(upcached_server* server);
void upcached_server_run(upcached_server* server);

#endif
