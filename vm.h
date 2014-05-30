#pragma once

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Internal memory
unsigned char  memory[4096];
unsigned char  reg8[16];
unsigned short reg16;
unsigned short stack[16];
unsigned short PC;
unsigned char  SP;

// Hardware
bool screen[2048];
bool keyboard[16];

// Fucntions
void VM_init();
void VM_play(char program[], size_t len);
void VM_parse(short opcode);
