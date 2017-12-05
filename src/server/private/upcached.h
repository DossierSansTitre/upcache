#ifndef INCLUDED_PRIVATE_UPCACHED_H
#define INCLUDED_PRIVATE_UPCACHED_H

#include <ev.h>

struct upcached_server_
{
    struct ev_loop* event_loop;
    int socket;
    int socket6;
    ev_io socket_watcher;
    ev_io socket_watcher6;
};

typedef struct upcached_server_ upcached_server;

/* server.c */
void upcached_server_init(upcached_server* server);
void upcached_server_run(upcached_server* server);

#endif
