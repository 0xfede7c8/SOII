#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

int read_file_bytes(const char* filename, char** bytes)
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
        fread(*bytes, filelen, 1, fileptr);
        fclose(fileptr);
    }
    else
    {
        print_errno();
        ret = 0;
    }
    return ret;
}

#endif
