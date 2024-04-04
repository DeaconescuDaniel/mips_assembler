#include <stdio.h>
#include "tokens.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


void insert_underscores(char *str, OpType opType) {
    int length = strlen(str);
    int *positions;
    int num_positions;
    switch (opType) {
        case R_TYPE:
            num_positions = 5;
            positions = (int *) malloc(sizeof(int) * num_positions);
            positions[0] = 6;
            positions[1] = 11;
            positions[2] = 16;
            positions[3] = 21;
            positions[4] = 26;
            break;
        case I_TYPE:
            num_positions = 3;
            positions = (int *) malloc(sizeof(int) * num_positions);
            positions[0] = 6;
            positions[1] = 11;
            positions[2] = 16;
            break;
        case J_TYPE:
            num_positions = 1;
            positions = (int *) malloc(sizeof(int) * num_positions);
            positions[0] = 6;
            break;
        case UNKNOWN_TYPE:
            num_positions = 0;
            positions = NULL;
            break;
    }
    for (int i = num_positions - 1; i >= 0; i--) {
        int pos = positions[i];
        if (pos >= 0 && pos < length) {
            memmove(str + pos + 1, str + pos, length - pos);
            str[pos] = '_';
            length++;
        }
    }

    int padding = 39 - length;
    if (padding > 0) {
        memmove(str + 1, str, length);
        str[0] = 'B';
        str[1] = '\"';
        length++;
        if (length > 1) {
            str[length++] = '\"';
        }
        if (length > 1) {
            str[length++] = ',';
        }
        for (int i = 0; i < padding - 1; i++) {
            str[length++] = ' ';
        }
    }

    str[length] = '\0';
}

void binary_convert(uint32_t num, char *binary_string, OpType OpType) {
    for (int i = 31; i >= 0; i--) {
        binary_string[31 - i] = ((num >> i) & 1) ? '1' : '0';
    }
    binary_string[32] = '\0';

    insert_underscores(binary_string, OpType);
}

int parseInputFile(const char *infile, const char *outFile, bool vhdl) {
    int line = 0;
    uint32_t currop = 0;
    FILE *fd = fopen(infile, "r");
    if (fd == NULL) {
        printf("Error reading file");
        return -2;
    }
    char buffer[256];
    char programBuffer[4096];
    char linebuffer[46];
    while (fgets(buffer, sizeof(buffer), fd) != NULL) {
        line++;
        TOK token;
        if ((token = findFirstToken(buffer)) == -1) {
            printf("Syntax error at line %d", line);
            fclose(fd);
            return -1;
        }
        currop = parseOperation(token, buffer);
        if (currop == -1) {
            printf("Syntax error at line %d", line);
            fclose(fd);
            return -1;
        } else {
            binary_convert(currop, linebuffer, (vhdl == true) ? getOpType(token) : UNKNOWN_TYPE);
            if (vhdl) {
                strcat(programBuffer,linebuffer);
                strcat(programBuffer,"\n");
            } else {
                snprintf(programBuffer + 33 * (line - 1), 35, "%s\n", linebuffer);
            }
        }
    }
    FILE *fd2 = fopen(outFile, "w");
    if (vhdl) {
        strcat(programBuffer,"others=>X\"00000000\"");
        fwrite(programBuffer, sizeof(char), line * sizeof(char) * 42 + 19, fd2);
    } else {
        fwrite(programBuffer, sizeof(char), line * sizeof(char) * 33, fd2);
    }
    fclose(fd);
    fclose(fd2);
    return 0;
}


int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: .\\acLinker.exe filename.txt filenameout [-v, --vhdl]");
        return -1;
    }
    bool vhdl = false;
    char *fileIn = NULL;
    char *fileOut = NULL;
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-v", 2) == 0 || strncmp(argv[i], "--vhdl", 6) == 0) {
            vhdl = true;
        } else if (fileIn == NULL) {
            fileIn = argv[i];
        } else if (fileOut == NULL) {
            fileOut = argv[i];
        } else {
            printf("Usage: .\\acLinker.exe filename.txt filenameout [-v, --vhdl]");
            return -1;
        }
    }
    parseInputFile(fileIn, fileOut, vhdl);
    return 0;
}
