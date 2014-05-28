#include "fs.h"

int loadProgram(FILE *file, char program[])
{
    int c;

    if (file) 
    {
        fread(program, sizeof(char), getFileLength(file), file);
        return 0;
    }
    else
    {
        return -1;
    }
}

int getFileLength(FILE* file)
{
    int size = -1;
    
    if (file)
    {
        fseek(file, 0L, SEEK_END);
        size = ftell(file);
        fseek(file, 0L, SEEK_SET);
    }

    return size;
}
