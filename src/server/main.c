#include <private/upcached.h>

int main(int argc, char** argv)
{
    upcached_server server;

    (void)argc;
    (void)argv;

    upcached_server_init(&server);
    upcached_server_run(&server);

    return 0;
}
