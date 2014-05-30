#include "vm.h"

void VM_init()
{
    // Reset VM state
    memset(memory, 0, sizeof(memory));
    memset(reg8, 0, sizeof(reg8));
    memset(stack, 0, sizeof(stack));
    memset(screen, false, sizeof(screen));
    memset(keyboard, false, sizeof(keyboard));
    reg16 = 0;
    PC = 0;
    SP = 0;

    // Add font sprites to memory
    // "0"
    memory[0] = 0xF0;
    memory[1] = 0x90;
    memory[2] = 0x90;
    memory[3] = 0x90;
    memory[4] = 0xF0;

    // "1"
    memory[5] = 0x20;
    memory[6] = 0x60;
    memory[7] = 0x20;
    memory[8] = 0x20;
    memory[9] = 0x70;

    // "2"
    memory[10] = 0xF0;
    memory[11] = 0x10;
    memory[12] = 0xF0;
    memory[13] = 0x80;
    memory[14] = 0xF0;
    
    // "3"
    memory[15] = 0xF0;
    memory[16] = 0x10;
    memory[17] = 0xF0;
    memory[18] = 0x10;
    memory[19] = 0xF0;

    // "4"
    memory[20] = 0x90;
    memory[21] = 0x90;
    memory[22] = 0xF0;
    memory[23] = 0x10;
    memory[24] = 0x10;

    // "5"
    memory[25] = 0xF0;
    memory[26] = 0x80;
    memory[27] = 0xF0;
    memory[28] = 0x10;
    memory[29] = 0xF0;

    // "6"
    memory[30] = 0xF0;
    memory[31] = 0x80;
    memory[32] = 0xF0;
    memory[33] = 0x90;
    memory[34] = 0xF0;

    // "7"
    memory[35] = 0xF0;
    memory[36] = 0x10;
    memory[37] = 0x20;
    memory[38] = 0x40;
    memory[39] = 0x40;

    // "8"
    memory[40] = 0xF0;
    memory[41] = 0x90;
    memory[42] = 0xF0;
    memory[43] = 0x90;
    memory[44] = 0xF0;

    // "9"
    memory[40] = 0xF0;
    memory[41] = 0x90;
    memory[42] = 0xF0;
    memory[43] = 0x10;
    memory[44] = 0xF0;

    // "A"
    memory[45] = 0xF0;
    memory[46] = 0x90;
    memory[47] = 0xF0;
    memory[48] = 0x90;
    memory[49] = 0x90;

    // "B"
    memory[50] = 0xE0;
    memory[51] = 0x90;
    memory[52] = 0xE0;
    memory[53] = 0x90;
    memory[54] = 0xE0;

    // "C"
    memory[55] = 0xF0;
    memory[56] = 0x80;
    memory[57] = 0x80;
    memory[58] = 0x80;
    memory[59] = 0xF0;

    // "D"
    memory[60] = 0xE0;
    memory[61] = 0x90;
    memory[62] = 0x90;
    memory[63] = 0x90;
    memory[64] = 0xE0;

    // "E"
    memory[65] = 0xF0;
    memory[66] = 0x80;
    memory[67] = 0xF0;
    memory[68] = 0x80;
    memory[69] = 0xF0;

    // "F"
    memory[70] = 0xF0;
    memory[71] = 0x80;
    memory[72] = 0xF0;
    memory[73] = 0x80;
    memory[74] = 0x80;
}

void VM_play(char program[], size_t len)
{
    for (int i = 0; i < len; i += 2) 
    {
        VM_parse((((short)program[i]) << 8) | program[i+1]);
    }
}

void VM_parse(short opcode)
{
    switch (opcode & 0xF000) // Left-most 4 bits
    {
    case 0x0000:
        switch(opcode)
        {
        case 0x00E0:
            // clear the display
            break;
        case 0x00EE:
            // return from subroutine
            break;
        default:
            // 0x0nnn (not implemented)
            break;
        }
        break;
    case 0x1000:
        // jump to location 0x1nnn
        break;
    case 0x2000:
        // call subroutine at 0x2nnn
        break;
    case 0x3000:
        // skip next instruction if Vx = kk (0x3xkk)
        break;
    case 0x4000:
        // skip next instruction if Vx != kk (0x4xkk)
        break;
    case 0x5000:
        // skip next instruction if Vx = Vy (0x5xy0)
        break;
    case 0x6000:
        // set Vx = kk (0x6xkk)
        break;
    case 0x7000:
        // set Vx = Vx + kk (0x7xkk)
        break;
    case 0x8000:
        // 0x8xy?
        switch (opcode & 0x000F) // right-most bit
        {
        case 0x0000:
            // set Vx = Vy
            break;
        case 0x0001:
            // set Vx = Vx OR Vy
            break;
        case 0x0002:
            // set Vx = Vx AND Vy
            break;
        case 0x0003:
            // set Vx = Vx XOR Vy
            break;
        case 0x0004:
            // set Vx = Vx + Vy; set VF = carry
            break;
        case 0x0005:
            // set Vx = Vx - Vy, set VF = NOT borrow
            break;
        case 0x0006:
            // set Vx = Vx SHR 1
            break;
        case 0x0007:
            // set Vx = Vy - Vx, set VF = NOT borrow.
            break;
        case 0x000E:
            // set Vx = Vx SHL 1
            break;
        }
        break;
    case 0x9000:
        // skip next instruction if Vx != Vy (0x9xy0)
        break;
    case 0xA000:
        // set set I = nnn (0xAnnn)
        break;
    case 0xB000:
        // jump to location nnn + V0 (0xBnnn)
        break;
    case 0xC000:
        // set Vx = random byte AND kk (0xCxkk)
        break;
    case 0xD000:
        // display n-byte sprite starting at memory location I at (Vx, Vy),
        // set VF = collision (0xDxyn)
        break;
    case 0xE000:
        // 0xEx??
        switch (opcode & 0x00FF) // right-most two bits
        {
        case 0x009E:
            // skip next instruction if key with the value of Vx is pressed.
            break;
        case 0x00A1:
            // skip next instruction if key with the value of Vx is not pressed.
            break;
        default:
            // bad instruction
            break;
        }
        break;
    case 0xF000:
        // 0xFx??
        switch (opcode & 0x00FF) // right-most two bits
        {
        case 0x0007:
            // set Vx = delay timer value.
            break;
        case 0x000A:
            // wait for a key press, store the value of the key in Vx
            break;
        case 0x0015:
            // set delay timer = Vx
            break;
        case 0x0018:
            // set sound timer = Vx
            break;
        case 0x001E:
            // set I = I + Vx
            break;
        case 0x0029:
            // set I = location of sprite fo digit Vx
            break;
        case 0x0033:
            // store BCD representation of Vx in memory locations I, I+1, and
            // I+2
            break;
        case 0x0055:
            // store registers V0 through Vx in memory starting at location I
            break;
        case 0x0065:
            // read registers V0 through Vx from memory starting at location I
            break;
        default:
            // bad instruction
            break;
        }
        break;
    default:
        // wtf?
        break;
    }
}
