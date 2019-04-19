#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include "net.h"
#include "translate_error.h"

#define NULL_PROTOCOL 0
#define SOCKET_FAILURE -1
#define FORK_FAILURE -1

int read_socket(const int fd, char* buffer, const size_t size)
{
    memset(buffer, 0, size);
    ssize_t n = read(fd, buffer, size-1);
    if (n < 0)
    {
        print_errno();
    }
    return n;
}

int write_socket(const int fd, char* buffer, const size_t size);

void check_fork_and_execute_cbs(int pid, void (*parent_fun)(int, int), void (*child_fun)(int, int), int fd)
{
    if (pid != -1)
    {
        if (pid == 0)
        {
            (*child_fun)(pid, fd);
        }
        else
        {
            (*parent_fun)(pid, fd);
        }
    }
}

int accept_connection_and_fork(const int srv_fd, int* new_fd)
{
    int ret_status;
    int new_server_fd;
    pid_t new_pid;
    socklen_t clilen;
    struct sockaddr_in cli_addr;

    clilen = sizeof(cli_addr);
    new_server_fd = accept(srv_fd, (struct sockaddr *) &cli_addr, &clilen);
    ret_status = new_server_fd != SOCKET_FAILURE;
    if (ret_status)
    {
        new_pid = fork();
        ret_status = new_pid != FORK_FAILURE;
        if (ret_status)
        {
            ret_status = new_pid;
            *new_fd = new_server_fd;
        }
        else
        {
            ret_status = FORK_FAILURE;
        }
    }
    else
    {
        ret_status = SOCKET_FAILURE;
    }

    if (ret_status == FORK_FAILURE)
    {
        print_errno();
    }
    return ret_status;
}

int connect_to_server(  const short socket_type,
                        const char* ip,
                        const int port,
                        int* fd)
{
    int socket_fd;
    struct sockaddr_in srv_addr;
    struct hostent* server;

    socket_fd = socket(AF_INET, socket_type, 0);
    int success = socket_fd != SOCKET_FAILURE;
    if (success)
    {
        server = gethostbyname(ip);
        success = server != NULL;
        if (success)
        {
            memset( (char *) &srv_addr, '0', sizeof(srv_addr) );
            srv_addr.sin_family = AF_INET;
            bcopy( (char *)server->h_addr, (char *)&srv_addr.sin_addr.s_addr, server->h_length);
            srv_addr.sin_port = htons(port);
            success = connect(socket_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) != SOCKET_FAILURE;
        }
    }

    if (!success)
    {
        print_errno();
    }
    else
    {
        *fd = socket_fd;
    }
    return success;
}

int create_server(  const short socket_type,
                    const int port,
                    const int max_connections,
                    int* fd)
{
    struct sockaddr_in srv_addr;
    int socket_fd = socket(AF_INET, socket_type, NULL_PROTOCOL);
    int success = socket_fd != SOCKET_FAILURE;

    if (success)
    {
        memset((char *) &srv_addr, 0, sizeof(srv_addr));
        srv_addr.sin_family = AF_INET;
        srv_addr.sin_addr.s_addr = INADDR_ANY;
        srv_addr.sin_port = htons(port);

        success = bind(socket_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr)) != SOCKET_FAILURE;
        if (success)
        {
            listen(socket_fd, max_connections);
        }
    }

    if(!success)
    {
        print_errno();
    }
    else
    {
        *fd = socket_fd;
    }
    return success;
}
