#include <stdio.h>
#include <string.h>

#include "net.h"
#include "translate_error.h"
#include "utils.h"

#include "validation.h"

#define MAX_BUF_SZ 50
#define MAX_USR_SZ 22
#define MAX_PSW_SZ 22

#define VALIDATION_STR "validated"
#define NO_VALIDATION_STR "not_validated"

int receive_validation(const int fd, char* usr, char* psw)
{
    int success = 0;
    // The protocol is first user and then password
    ssize_t n = read_socket(fd, usr, MAX_USR_SZ);
    if (n > 0 && n < MAX_USR_SZ)
    {
        n = read_socket(fd, psw, MAX_USR_SZ);
        success = n > 0 && n < MAX_USR_SZ;
    }
    return success;
}

int send_validation(const int fd, const char* usr, const char* psw)
{
    int success = 0;
    // The protocol is first user and then password
    ssize_t n = write_socket(fd, usr, MAX_USR_SZ);
    if (n > 0 && n < MAX_USR_SZ)
    {
        n = write_socket(fd, psw, MAX_USR_SZ);
        success = n > 0 && n < MAX_USR_SZ;
    }
    return success;
}

int validate_server(const int fd)
{
    int validated = 0;
    char usr[MAX_USR_SZ];
    char received_psw[MAX_PSW_SZ];
    char* psw;
    // We receive the credentials from the user
    if (receive_validation(fd, usr, received_psw))
    {
        // Read secrets file
        const int success = read_file_bytes("secret.key", &psw);
        if (success)
        {
            // Compare pswds
            validated = strcmp(psw, received_psw) == 0;
            free(psw);
            if (validated)
            {
                // Tell user if succeded
                const int n = write_socket(fd, VALIDATION_STR, strlen(VALIDATION_STR) + 1);
                validated = n > 0;
                if (!validated)
                {
                    perror("Couldn't send validated response.\n");
                }
            }
            else
            {
                const int n = write_socket(fd, NO_VALIDATION_STR, strlen(NO_VALIDATION_STR) + 1);
                if (n < 0)
                {
                    perror("Couldn't send not validated response \n");
                }
            }
        }
    }
    return validated;
}

int validate_client(const int fd, const char* usr, const char* psw)
{
    int validated = 0;
    char validation_msg[MAX_BUF_SZ];
    // Send credentials to user
    if (send_validation(fd, usr, psw))
    {
        // Check if we succeded
        const int n = read_socket(fd, validation_msg, MAX_BUF_SZ);
        if (n > 0)
        {
            validated = strcmp(validation_msg, VALIDATION_STR) == 0;
        }
    }
    return validated;
}

int validate_client_with_prompt(const int fd)
{
    char usr[MAX_USR_SZ];
    char psw[MAX_PSW_SZ];
    memset(usr, '\0', MAX_USR_SZ);
    memset(psw, '\0', MAX_PSW_SZ);

    printf("user: ");
    fgets(usr, MAX_USR_SZ-1, stdin);
    printf("password: ");
    fgets(psw, MAX_PSW_SZ-1, stdin);

    return validate_client(fd, usr, psw);
}
