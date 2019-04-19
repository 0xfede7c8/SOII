#ifndef TRANSLATE_ERROR_H
#define TRANSLATE_ERROR_H

#include <stdio.h>
#include <errno.h>
#include <string.h>

void print_errno()
{
    perror(strerror(errno));
}

#endif
