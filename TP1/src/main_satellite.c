#include <stdlib.h>

#include "satellite.h"

int main(__attribute__((unused)) int argc, char** argv)
{
    int success;
    const char* ip = argv[1];
    const int port = atoi(argv[2]);
    if (run_satellite_client(ip, port))
    {
        success = EXIT_SUCCESS;
    }
    else
    {
        success = EXIT_FAILURE;
    }
    return success;
}
