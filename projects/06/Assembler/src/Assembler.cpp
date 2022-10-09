#include "../include/AllHeaders.h"
#include "../include/Parser.h"
#include "../include/Code.h"

std::string decimalToBinary(std::string);

int main(int argc, char *argv[])
{
    // check number of argument
    if (argc != 2)
    {
        fprintf(stderr, "SYNOPSIS: Assembler XX.asm\n");
        exit(1);
    }

    // get .asm file path
    std::string asmFileName(argv[1]);
    std::string asmFilePath = "./" + asmFileName;

    // create and open .hack file
    size_t pos = asmFileName.find(".asm");
    if (pos == std::string::npos)
    {
        fprintf(stderr, "invalid extension: .asm is only valid\n");
        exit(1);
    }
    std::string hackFileName = asmFileName.substr(0, pos) + ".hack";
    std::cout << hackFileName << std::endl;
    FILE *fp = fopen(hackFileName.c_str(), "w");

    // create object
    Parser *parser = new Parser(asmFilePath);
    Code *code = new Code();

    // read .asm, assemble line, and write binary into .hack
    int debugCount = 0;
    while (parser->hasMoreCommands())
    {
        parser->advance();
        std::string binCode = "";
        if (parser->commandType() == A_COMMAND)
        {
            binCode = decimalToBinary(parser->symbol());
        }
        else if (parser->commandType() == L_COMMAND)
        {
            // coding later
        }
        else if (parser->commandType() == C_COMMAND)
        {
            std::string destMnemonic = parser->dest();
            std::string compMnemonic = parser->comp();
            std::string jumpMnemonic = parser->jump();
            // printf("dest: %s, %s\n", destMnemonic.c_str(), code->dest(destMnemonic).c_str());
            // printf("comp: %s, %s\n", compMnemonic.c_str(), code->comp(compMnemonic).c_str());
            // printf("jump: %s, %s\n", jumpMnemonic.c_str(), code->jump(jumpMnemonic).c_str());
            binCode = "111" + code->comp(compMnemonic) + code->dest(destMnemonic) + code->jump(jumpMnemonic);
        }
        else
        {
            break;
        }
        binCode += '\n';
        fprintf(fp, "%s", binCode.c_str());
        // std::cout << "L: " << ++debugCount << " | " << parser->currentCommand << std::endl;
        // std::cout << binCode << std::endl;
    }

    // erase object
    delete parser;
    delete code;
    fclose(fp);

    exit(0);
}

std::string decimalToBinary(std::string dec)
{
    int decNum = stoi(dec);
    std::string ret = "";
    while (decNum > 0)
    {
        ret = std::to_string(decNum % 2) + ret;
        decNum /= 2;
    }
    while (ret.length() < COMMAND_LENGTH)
    {
        ret = '0' + ret;
    }
    return ret;
}
