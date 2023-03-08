#ifndef _CODEWRITER_H_
#define _CODEWRITER_H_

#include "Common.h"

class CodeWriter
{
private:
	FILE *fp;

public:
	CodeWriter(std::string);
	~CodeWriter();
	void setFileName(std::string);
	void writeArithmetic(std::string);
	void writePushPop(int, std::string, int);
	void close();
};

#endif
