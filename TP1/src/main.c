#include <stdlib.h>

#include "ground_station.h"

int main(__attribute__((unused)) int argc, char** argv)
{
    const int res = run_ground_server(atoi(argv[1]));
    return res;
}
