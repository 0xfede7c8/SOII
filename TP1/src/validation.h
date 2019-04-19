#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>

#include "translate_error.h"
#include "utils.h"

int validate_password(__attribute__((unused)) const char* password)
{
    char* pass;
    const int success = read_file_bytes("secret.key", &pass);
    if (success)
    {
        printf("%s", pass);
        free(pass);
    }
    return 1;
}

#endif
