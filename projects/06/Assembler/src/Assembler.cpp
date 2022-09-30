#include <iostream>
#include <stdio.h>

const int PATH_LENGTH = 128;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "SYNOPSIS: Assembler XX.asm");
        exit(1);
    }

    std::string asmFileName(argv[1]);
    std::string asmFilePath = "./" + asmFileName;
    FILE *asmFile = fopen(asmFilePath.c_str(), "r");

    int BUF_SIZE = 256;
    char buf[BUF_SIZE];

    while (fgets(buf, BUF_SIZE, asmFile) != NULL)
    {
        if (buf[0] == '/' || buf[0] == '\n')
        {
            continue;
        }
        fputs(buf, stdout);
    }

    fclose(asmFile);

    exit(0);
}
