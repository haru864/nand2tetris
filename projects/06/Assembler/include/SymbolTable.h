#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include "AllHeaders.h"

class SymbolTable
{
private:
    std::map<std::string, int> symbolTable;
    int symbolAddress;
    int variableAddress;
    std::queue<std::string> variableCandidate;

public:
    SymbolTable();
    ~SymbolTable();
    int getSymbolAddress();
    int getVariableAddress();
    void increaseSymbolAddress();
    void increaseVariableAddress();
    void addCandidate(std::string);
    void addVariableToTable();
    void addEntry(std::string, int);
    bool contains(std::string);
    int getAddress(std::string);
};

#endif
