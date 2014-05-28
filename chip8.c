#include <stdio.h>
#include "fs.h"
#include "vm.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: chip8 <filename>\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Can't open file: %s\n", argv[1]);
        return 0;
    }

    int filelen = getFileLength(file);
    char program[filelen];

    loadProgram(file, program);  
    fclose(file);

    VM_init();
    VM_play(program, filelen);
}
