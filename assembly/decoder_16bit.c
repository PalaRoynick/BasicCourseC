//-----------------------------------------------------------------------------
//
// C learning excercise course
//
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
#include "defs.h"

void output_unary_op(unsigned short v) {
    if (v & 0x04) {
        printf("OUT ");
    } else {
        printf("IN ");
    }
    return;
}

void output_binary_op(unsigned short v) {
    unsigned short dispatch_bytes = (v & 0x30) >> 4;
#ifdef DEBUG
    printf("Binary operation bytes: %hu\n", dispatch_bytes);
#endif
    switch ((v & 0x30) >> 4)
    {
    case 0:
        printf("ADD ");
        break;
    case 1:
        printf("SUB ");
        break;
    case 2:
        printf("MUL ");
        break;
    case 3:
        printf("DIV ");
        break;
    default:
        break;
    };
    return;
}

void print_register(unsigned short reg_bytes) {
    switch (reg_bytes)
    {
    case 0:
        printf("A");
        break;
    case 1:
        printf("B");
        break;
    case 2:
        printf("C");
        break;
    case 3:
        printf("D");
        break;
    default:
        printf("WRONG");
        break;
    }
    return;
}

void output_binop_registers(unsigned short v) {
    unsigned short regb;
    output_binary_op(v);
    regb = (v & 0x0c) >> 2;
    print_register(regb);
    printf(", ");
    regb = v & 0x03;
    print_register(regb);
    printf("\n");
    return;
}

void output_unop_registers(unsigned short v) {
    output_unary_op(v);
    print_register(v & 0x03);
    printf("\n");
    return;
}

void decoder_16bit(unsigned short v)
{
    unsigned short hb = v >> 7, hbs = v & 0xc0;
#ifdef DEBUG
    printf("%hu \n",  hb);
#endif
    if (!hb) { // MOVI
        printf("MOVI D, %hu\n", v & 0x7f);
    } else {
        if (hbs == 0x80) { // ADD, SUB, MUL, DIV
            output_binop_registers(v);
        } else { // IN, OUT
            output_unop_registers(v);
        }
    }
    return;
}

int main() {
    unsigned short v;
    while (1 == scanf(" 0x%hx", &v)) {
#ifdef DEBUG
        printf("The new entered value: 0x%02hx (hexagonal), %hu (decimal)\n", v, v);
#endif
        decoder_16bit(v);
    }
    if (feof(stdin)) {
        printf("End of file reached\n");
    } else if (ferror(stdin)) {
        printf("Error occured while reading input\n");
    } else {
        printf("Invalid input occured\n");
    }
    return 0;
}