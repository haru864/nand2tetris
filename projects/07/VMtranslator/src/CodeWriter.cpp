#include "../include/CodeWriter.h"

CodeWriter::CodeWriter(std::string fileName)
{
	CodeWriter::fp = fopen(fileName.c_str(), "w");
	if (!fp)
	{
		exit_error("fail to initialize CodeWriter");
	}
}

CodeWriter::~CodeWriter()
{
	fclose(CodeWriter::fp);
}

void CodeWriter::setFileName(std::string fileName)
{
}

void CodeWriter::writeArithmetic(std::string command)
{
}

void CodeWriter::writePushPop(int command, std::string segment, int index)
{
}

void CodeWriter::close()
{
}
