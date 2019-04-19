#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "translate_error.h"

void print_errno()
{
    perror(strerror(errno));
}
