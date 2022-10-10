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
        SymbolTable::usedAddress.insert(i);
    }
    SymbolTable::currentAddress = 16;

    SymbolTable::symbolTable["SCREEN"] = 16384;
    SymbolTable::symbolTable["KBD"] = 24576;
    SymbolTable::usedAddress.insert(16384);
    SymbolTable::usedAddress.insert(24576);
}

SymbolTable::~SymbolTable() {}

int SymbolTable::getCurrentAddress()
{
    while (SymbolTable::usedAddress.count(SymbolTable::currentAddress) != 0)
    {
        SymbolTable::currentAddress++;
    }
    return SymbolTable::currentAddress;
}

void SymbolTable::addEntry(std::string symbol, int address)
{
    SymbolTable::symbolTable[symbol] = address;
    SymbolTable::usedAddress.insert(address);
}

bool SymbolTable::contains(std::string symbol)
{
    return SymbolTable::symbolTable.count(symbol);
}

int SymbolTable::getAddress(std::string symbol)
{
    return SymbolTable::symbolTable[symbol];
}
