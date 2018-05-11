#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
    if (argc < 2) return -1;
    const char* program = argv[1];
    char* buf = calloc(100000, sizeof(char));
    char* ptr = buf;
    for (size_t i = 0; i < strlen(program); i++) {
        const char operator = program[i];
        switch (operator) {
        case('>'):
            ptr++;
            break;
        case('<'):
            ptr--;
            break;
        case('+'):
            (*ptr)++;
            break;
        case('-'):
            (*ptr)--;
            break;
        case('.'):
            putchar(ptr);
            break;
        case(','):
            getchar();
            break;
        case('['):
            if (*ptr != 0) {
                continue;
            }
            size_t nest = 1;
            while (true) {
                i++;
                if (program[i] == '[') {
                    nest++;
                    continue;
                }
                if (program[i] == ']') {
                    nest--;
                    if (nest == 0) {
                        break;
                    }
                }
            }
            break;
        case(']'):
            if (*ptr = 0) {
                continue;
            }
            size_t nest = 1;
            while (true) {
                i--;
                if (program[i] == ']') {
                    nest++;
                    continue;
                }
                if (program[i] == '[') {
                    nest--;
                    if (nest == 0) {
                        break;
                    }
                }
            }
            break;
    }
    free(buf);
    return 0;
}
