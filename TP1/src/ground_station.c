#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "net.h"
#include "server.h"
#include "validation.h"

void server_fun(__attribute__((unused)) int pid, __attribute__((unused)) int fd)
{
    printf("Server delegated work to child.\n");
}

void child_server_fun(__attribute__((unused)) int pid, int fd)
{
    char buffer[MAX_SZ];
    ssize_t n = read_socket(fd, buffer, MAX_SZ);
    printf("%s %li", buffer, n);
    if (validate_password(buffer))
    {
        printf("password correct");
    }
    else
    {
        printf("Password incorrect.\n");
    }
    close(fd);
    exit(0);
}

int run_ground_server()
{
    int srv_fd;
    int success = create_server(SOCK_STREAM, 5002, 5, &srv_fd);
    if (success)
    {
        while(1)
        {
            int new_fd;
            printf("Waiting for connections...\n");
            const int pid = accept_connection_and_fork(srv_fd, &new_fd);
            check_fork_and_execute_cbs(pid, &server_fun, &child_server_fun, new_fd);
        }
    }
    else
    {
        perror("Can't create server.\n");
        return -1;
    }
}
