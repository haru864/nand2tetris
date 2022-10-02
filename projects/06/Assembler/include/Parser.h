#ifndef _PARSER_H_
#define _PARSER_H_

#include "AllHeaders.h"

#define BUF_SIZE 256

class Parser
{
private:
    FILE *asmFile;
    char buf[BUF_SIZE];
    std::string currentCommand;

public:
    Parser(std::string path);
    ~Parser();
    bool hasMoreCommands();
    void advance();
    int commandType();
    std::string symbol();
    std::string dest();
    std::string comp();
    std::string jump();
};

#endif
