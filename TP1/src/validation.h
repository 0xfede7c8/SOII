#ifndef VALIDATION_H
#define VALIDATION_H

int send_validation(const int fd, const char* usr, const char* psw);
int receive_validation(const int fd, char* usr, char* psw);
int validate_client(const int fd, const char* user, const char* password);
int validate_server(const int fd);
int validate_client_with_prompt(const int fd);

#endif
