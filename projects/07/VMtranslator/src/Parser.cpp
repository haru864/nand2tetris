#include "../include/Parser.h"

Parser::Parser(std::string fileName)
{
	Parser::fp = fopen(fileName.c_str(), "r");
	Parser::currentCommand = (char *)malloc(CMD_SIZE);
	if (!fp || !currentCommand)
	{
		exit_error("fail to initialize Parser");
	}
}

Parser::~Parser()
{
	fclose(Parser::fp);
	safe_free(Parser::currentCommand);
}

bool Parser::hasMoreCommands()
{
	return feof(Parser::fp) != 0;
}

void Parser::advance()
{
}

int Parser::commandType()
{
}

std::string Parser::arg1()
{
}

int Parser::arg2()
{
}
