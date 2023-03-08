#ifndef _PARSER_H_
#define _PARSER_H_

#include "Common.h"

#define CMD_SIZE (size_t)256

class Parser
{
private:
	FILE *fp;
	char *currentCommand;

public:
	Parser(std::string);
	~Parser();
	bool hasMoreCommands();
	void advance();
	int commandType();
	std::string arg1();
	int arg2();
};

#endif
