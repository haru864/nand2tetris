#ifndef _CODEWRITER_H_
#define _CODEWRITER_H_

#include "AllHeaders.h"

class CodeWriter
{
private:
    /* data */
public:
    CodeWriter(FILE *);
    ~CodeWriter();
    void setFileName(std::string);
    void writeArithmetic(std::string);
    void writePushPop(int, std::string, int);
    void close();
};

#endif
