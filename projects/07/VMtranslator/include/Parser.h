#ifndef _PARSER_H_
#define _PARSER_H_

#include "AllHeaders.h"

class Parser
{
private:
    /* data */
public:
    Parser(FILE *);
    ~Parser();
    bool hasMoreCommands();
    void advance();
    int commandType();
    std::string arg1();
    int arg2();
};

#endif
