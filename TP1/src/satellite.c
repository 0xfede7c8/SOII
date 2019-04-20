#include <stdio.h>

#include "net.h"
#include "validation.h"

#include "satellite.h"

int run_satellite_client(const char* ip, const int port)
{
    int cli_fd;
    int success = connect_to_server(SOCK_STREAM, ip, port, &cli_fd);
    if (success)
    {
        success = validate_client_with_prompt(cli_fd);
        if (success)
        {
            printf("Login successful.\n");
        }
        else
        {
            printf("Failed to login.\n");
        }
    }
    return success;
}
