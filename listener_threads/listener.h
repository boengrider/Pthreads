#include <arpa/inet.h>
#include <bits/pthreadtypes.h>
#include <stdint.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

struct thread_list
{
    uint32_t count;
    pthread_t threads[20];
};

typedef enum thread_startup_state_
{
    Operational,
    Failed,
    Unknown,
} thread_startup_state_t;

struct thread_startup_info
{
    thread_startup_state_t state;
};

typedef struct listener_user_args_
{
    char terminatingCharacter;
    struct thread_startup_info info;
    struct thread_list *list;
} listener_user_args_t;

typedef struct listener_user_result_
{
    int threadErrno;
} listener_user_result_t;

typedef struct listener_network_args_
{
    char *bind_address;
    int protocol;
    int port;
    struct thread_startup_info info;
} listener_network_args_t;

typedef struct listener_network_result_
{
    int threadErrno;
} listener_network_result_t;

void *listener_network(void *args);
void *listener_user(void *args);


