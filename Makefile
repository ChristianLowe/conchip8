chip8: chip8.c fs.c vm.c
	gcc -std=c99 -g -o chip8.out chip8.c fs.c vm.c -I.
