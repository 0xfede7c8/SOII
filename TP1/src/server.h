#ifndef SERVER_H
#define SERVER_H

// Parent server callback
void server_fun(int pid, int fd);

// Child server callback
void child_server_fun(int pid, int fd);

#endif
