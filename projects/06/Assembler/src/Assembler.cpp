#include "../include/AllHeaders.h"
#include "../include/Parser.h"
#include "../include/Code.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "SYNOPSIS: Assembler XX.asm");
        exit(1);
    }

    init();

    std::string asmFileName(argv[1]);
    std::string asmFilePath = "./" + asmFileName;
    Parser parser(asmFilePath);

    // FILE *asmFile = fopen(asmFilePath.c_str(), "r");
    // int BUF_SIZE = 256;
    // char buf[BUF_SIZE];

    // while (fgets(buf, BUF_SIZE, asmFile) != NULL)
    // {
    //     if (buf[0] == '/' || buf[0] == '\n')
    //     {
    //         continue;
    //     }
    //     fputs(buf, stdout);
    // }

    // fclose(asmFile);

    exit(0);
}
