#ifndef SRV_H
#define SRV_H

#include "sys/socket.h"


/*  Creates and binds socket. Returns false if failure, true otherwise.
    fd is written on success only
*/

#define MAX_SZ 1024u

int create_server(  const short socket_type,
                    const int port,
                    const int max_connections,
                    int* fd);

int connect_to_server(  const short socket_type,
                        const char* ip,
                        const int port,
                        int* fd);

/*  Accepts a connection and spawns a process for it.
    Returns 1 if in child process
    Returns 0 if in parent
    Returns -1 if failure
*/
int accept_connection_and_fork(const int srv_fd, int* new_fd);

// This checks for child and parent process and executes the callback accordingly
void check_fork_and_execute_cbs(int pid, void (*parent_fun)(int, int), void (*child_fun)(int, int), int fd);


int read_socket(int fd, char* buffer, size_t size);

int write_socket(int fd, char* buffer, size_t size);
#endif
