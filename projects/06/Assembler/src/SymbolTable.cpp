#include "../include/SymbolTable.h"

SymbolTable::SymbolTable()
{
    SymbolTable::symbolTable["SP"] = 0;
    SymbolTable::symbolTable["LCL"] = 1;
    SymbolTable::symbolTable["ARG"] = 2;
    SymbolTable::symbolTable["THIS"] = 3;
    SymbolTable::symbolTable["THAT"] = 4;

    for (int i = 0; i <= 15; i++)
    {
        std::string s = "R" + std::to_string(i);
        SymbolTable::symbolTable[s] = i;
    }
    SymbolTable::symbolAddress = 0;
    SymbolTable::variableAddress = 16;

    SymbolTable::symbolTable["SCREEN"] = SCREEN_ADDRESS;
    SymbolTable::symbolTable["KBD"] = KBD_ADDRESS;
}

SymbolTable::~SymbolTable() {}

int SymbolTable::getSymbolAddress()
{
    return SymbolTable::symbolAddress;
}

int SymbolTable::getVariableAddress()
{
    return SymbolTable::variableAddress;
}

void SymbolTable::increaseSymbolAddress()
{
    SymbolTable::symbolAddress++;
}

void SymbolTable::increaseVariableAddress()
{
    SymbolTable::variableAddress++;
}

void SymbolTable::addEntry(std::string symbol, int address)
{
    SymbolTable::symbolTable[symbol] = address;
}

bool SymbolTable::contains(std::string symbol)
{
    return SymbolTable::symbolTable.count(symbol);
}

int SymbolTable::getAddress(std::string symbol)
{
    return SymbolTable::symbolTable[symbol];
}

bool SymbolTable::isAvailableAddr(int address)
{
    return (address > 15 && address < SCREEN_ADDRESS);
}
