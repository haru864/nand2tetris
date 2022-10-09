#include "../include/Code.h"

Code::Code()
{
    COMP_TABLE[""] = "0000000";
    COMP_TABLE["0"] = "0101010";
    COMP_TABLE["1"] = "0111111";
    COMP_TABLE["-1"] = "0111010";
    COMP_TABLE["D"] = "0001100";
    COMP_TABLE["A"] = "0110000";
    COMP_TABLE["!D"] = "0001101";
    COMP_TABLE["!A"] = "0110001";
    COMP_TABLE["-D"] = "0001111";
    COMP_TABLE["-A"] = "0110011";
    COMP_TABLE["D+1"] = "0011111";
    COMP_TABLE["A+1"] = "0110111";
    COMP_TABLE["D-1"] = "0001110";
    COMP_TABLE["A-1"] = "0110010";
    COMP_TABLE["D+A"] = "0000010";
    COMP_TABLE["D-A"] = "0010011";
    COMP_TABLE["A-D"] = "0000111";
    COMP_TABLE["D&A"] = "0000000";
    COMP_TABLE["D|A"] = "0010101";
    // // COMP_TABLE[] = "1101010"; // not allocated
    // // COMP_TABLE[] = "1111111"; // not allocated
    // // COMP_TABLE[] = "1111010"; // not allocated
    // // COMP_TABLE[] = "1001100"; // not allocated
    COMP_TABLE["M"] = "1110000";
    // // COMP_TABLE[] = "1001101"; // not allocated
    COMP_TABLE["!M"] = "1110001";
    // // COMP_TABLE[] = "1001111"; // not allocated
    COMP_TABLE["-M"] = "1110011";
    // // COMP_TABLE[] = "1011111"; // not allocated
    COMP_TABLE["M+1"] = "1110111";
    // // COMP_TABLE[] = "1001110"; // not allocated
    COMP_TABLE["M-1"] = "1110010";
    COMP_TABLE["D+M"] = "1000010";
    COMP_TABLE["D-M"] = "1010011";
    COMP_TABLE["M-D"] = "1000111";
    COMP_TABLE["D&M"] = "1000000";
    COMP_TABLE["D|M"] = "1010101";

    DEST_TABLE[""] = "000";
    DEST_TABLE["M"] = "001";
    DEST_TABLE["D"] = "010";
    DEST_TABLE["MD"] = "011";
    DEST_TABLE["A"] = "100";
    DEST_TABLE["AM"] = "101";
    DEST_TABLE["AD"] = "110";
    DEST_TABLE["AMD"] = "111";

    JUMP_TABLE[""] = "000";
    JUMP_TABLE["JGT"] = "001";
    JUMP_TABLE["JEQ"] = "010";
    JUMP_TABLE["JGE"] = "011";
    JUMP_TABLE["JLT"] = "100";
    JUMP_TABLE["JNE"] = "101";
    JUMP_TABLE["JLE"] = "110";
    JUMP_TABLE["JMP"] = "111";
}

Code::~Code() {}

std::string Code::dest(std::string mnemonic)
{
    return DEST_TABLE[mnemonic];
}

std::string Code::comp(std::string mnemonic)
{
    return COMP_TABLE[mnemonic];
}

std::string Code::jump(std::string mnemonic)
{
    return JUMP_TABLE[mnemonic];
}
