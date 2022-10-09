#ifndef _CODE_H_
#define _CODE_H_

#include "AllHeaders.h"

class Code
{
public:
    std::map<std::string, std::string> COMP_TABLE, DEST_TABLE, JUMP_TABLE;
    Code();
    ~Code();
    std::string dest(std::string mnemonic);
    std::string comp(std::string mnemonic);
    std::string jump(std::string mnemonic);
};

#endif
