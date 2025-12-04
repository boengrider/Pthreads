#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>


typedef struct listener_network_args_
{
    char *bind_address;
    int protocol;
    int port;
} listener_network_args_t;

typedef struct listener_network_result_
{
    int threadErrno;
} listener_network_result_t;

void *listener_network(void *args);
void *listener_user(void *args);


