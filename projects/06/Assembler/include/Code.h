#ifndef _CODE_H_
#define _CODE_H_

#include "AllHeaders.h"

class Code
{
public:
    static std::string dest(std::string mnemonic);
    static std::string comp(std::string mnemonic);
    static std::string jump(std::string mnemonic);
};

#endif