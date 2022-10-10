#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include "AllHeaders.h"

class SymbolTable
{
private:
    std::map<std::string, int> symbolTable;
    std::set<int> usedAddress;
    int currentAddress;

public:
    SymbolTable();
    ~SymbolTable();
    int getCurrentAddress();
    void addEntry(std::string, int);
    bool contains(std::string);
    int getAddress(std::string);
};

#endif
