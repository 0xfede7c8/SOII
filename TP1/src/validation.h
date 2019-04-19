#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>

#include "translate_error.h"

int validate_password(const char* password, const char* pass_file)
{
    (void*) password; //unused
    char* pass = read_file_bytes("secret.key");
    print(pass);
    return 1;
}


// Read the bytes of the password from a file. Bytes should be freed afterwards
int read_file_bytes(const char* filename)
{
    int ret = 1;
    long filelen;
    FILE *fileptr = fopen(filename, "rb");
    if (fileptr != NULL)
    {
        fseek(fileptr, 0, SEEK_END);
        filelen = ftell(fileptr);
        rewind(fileptr);

        *bytes = (char *)malloc((filelen)*sizeof(char));
        fread(buffer, filelen, 1, fileptr);
        fclose(fileptr);
    }
    else
    {
        print_error();
        ret = 0;
    }
    return ret;
}

#endif
