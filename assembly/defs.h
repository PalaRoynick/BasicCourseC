//-----------------------------------------------------------------------------
//
// C learning excercise course
//
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
#ifndef H_ASSEMBLY
#define H_ASSEMBLY

#include "stdio.h"

#define MAX_LINE_LEN   256
#define MAX_LINE_WORDS   8

typedef enum {
    MOVI,
    ADD,
    SUB,
    MUL,
    DIV,
    IN,
    OUT
} OP;

void coder_16bit(const char *cmd);
void decoder_16bit(unsigned short v);

#endif