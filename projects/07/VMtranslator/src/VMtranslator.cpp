#include "../include/Common.h"
#include "../include/Parser.h"
#include "../include/CodeWriter.h"

using namespace std;

void exit_error(string);

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		exit_error("setting no argument");
	}

	string vmFileName(argv[1]);
	auto pos = vmFileName.find(".vm");
	if (pos == string::npos)
	{
		exit_error("set Xxx.vm as argument");
	}
	string asmFileName = vmFileName.substr(0, pos) + ".asm";
	// printf("%s\n", asmFileName.c_str());

	// FILE *inFile = fopen(vmFileName.c_str(), "r");
	// FILE *outFile = fopen(asmFileName.c_str(), "w");
	// if (!inFile || !outFile)
	// {
	// 	exit_error("fail to open file");
	// }

	Parser *parser = new Parser(vmFileName);
	CodeWriter *codeWriter = new CodeWriter(asmFileName);

	delete parser;
	delete codeWriter;

	return EXIT_SUCCESS;
}
