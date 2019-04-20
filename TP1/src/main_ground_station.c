#include <stdlib.h>

#include "ground_station.h"

int main(__attribute__((unused)) int argc, char** argv)
{
    int success;
    const int port = atoi(argv[1]);
    if (run_ground_server(port))
    {
        success = EXIT_SUCCESS;
    }
    else
    {
        success = EXIT_FAILURE;
    }
    return success;
}
