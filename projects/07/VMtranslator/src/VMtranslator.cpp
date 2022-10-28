#include "../include/AllHeaders.h"

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
	printf("%s\n", asmFileName.c_str());

	return EXIT_SUCCESS;
}

void exit_error(string message)
{
	fprintf(stderr, "error: %s\n", message.c_str());
	exit(EXIT_FAILURE);
}