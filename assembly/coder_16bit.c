//-----------------------------------------------------------------------------
//
// C learning excercise course
//
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
#include "stdlib.h"
#include "assert.h"
#include "string.h"

#include "defs.h"

/*
    Takes the next command, separators
    Returns tokenized array of words and the size of the array
*/
char** tokenize(const char *cmd, const char *sep, size_t* sz) {
    assert(sz != NULL);
    *sz = 0;

    char **words = malloc(MAX_LINE_WORDS * sizeof(char));
    if (words == NULL) {
        perror("[tokenize]: Failed to allocate memory for words array");
        return NULL;
    }

    size_t len = strlen(cmd);
    char *cmd_ = malloc(len * sizeof(char));
    strcpy(cmd_, cmd);
    // remove trailing new line character if needed
    if ((len > 0) && (cmd[len - 1] == '\n')) {
        cmd_[len - 1] = '\0';
    }
    char *word = strtok(cmd_, sep);
    while (word != NULL) {
        assert(*sz < MAX_LINE_WORDS);
        words[*sz] = malloc( (strlen(word) + 1) * sizeof(char) );

        if (words[*sz] == NULL) {
            perror("[tokenize]: Failed to allocate memory for a new word");
            // free the previously allocated memory
            for (size_t i = 0; i < *sz; ++i) {
                free(words[i]);
            }
            free(words);
            return NULL;
        }

        strcpy(words[*sz], word);
        word = strtok(NULL, sep);
        (*sz)++;
    }
    return words;
}

unsigned short bits_view_of_reg(char reg) {
    unsigned short bits = 0;
    switch (reg)
    {
    case 'A':
        bits = 0;
        break;
    case 'B':
        bits = 1;
        break;
    case 'C':
        bits = 2;
        break;
    case 'D':
        bits = 3;
        break;
    default:
        break;
    }
    return bits;
}

void handle_unop(char **words, OP op) {
    unsigned short reg_bits = 0;
    if (MOVI == op) {
        // TODO what if not a unsigned short number? And less than 128
        unsigned short num = (unsigned short)strtoul(words[2], NULL, 0);
        printf("0x%02hx ", num);
        return;
    }
    reg_bits = bits_view_of_reg(words[1][0]);
    if (IN == op) {
        reg_bits |= 0xc0;
    }
    else if (OUT == op) {
        reg_bits |= 0xc4;
    }
    printf("0x%02hx ", reg_bits);
    return;
}

void handle_binop(char **words, OP op) {

}

void coder_16bit(const char *cmd) {
    size_t sz = 0;
    char *word = NULL;
    char **words = tokenize(cmd, ", ", &sz);
    if (sz > 3) {
        printf("Too many words in the command: %s\n", cmd);
        abort();
    }

    word = words[0];
    // TODO error handling if a wrong keyword
    switch (word[0])
    {
    case 'M':
        if (word[1] == 'O') handle_unop(words, MOVI);
        else if (word[1] == 'U') handle_binop(words, MUL);
        break;
    case 'A':
        handle_binop(words, ADD);
        break;
    case 'S':
        handle_binop(words, SUB);
        break;
    case 'D':
        handle_binop(words, DIV);
        break;
    case 'I':
        handle_unop(words, IN);
        break;
    case 'O':
        handle_unop(words, OUT);
        break;
    default:
        break;
    }

    for (size_t i = 0; i < sz; i++) {
#ifdef DEBUG
        printf("%s ", words[i]);
#endif
        const char *word = words[i];

    }
#ifdef DEBUG
    printf("\n");
#endif


}

int main() {
    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), stdin)) {
#ifdef DEBUG
        printf("The new entered command: %s\n", line);
#endif
        coder_16bit(line);
    }
    printf("\n");
    if (feof(stdin)) {
        printf("End of file reached\n");
    } else if (ferror(stdin)) {
        printf("Error occured while reading input\n");
    } else {
        printf("Invalid input occured\n");
    }
    return 0;
}