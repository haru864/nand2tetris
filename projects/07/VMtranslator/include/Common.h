#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>

#define C_ARITHMETIC 0
#define C_PUSH 1
#define C_POP 2
#define C_LABEL 3
#define C_GOTO 4
#define C_IF 5
#define C_FUNCTION 6
#define C_RETURN 7
#define C_CALL 8

void safe_free(void *p)
{
	free(p);
	p = NULL;
}

void exit_error(std::string message)
{
	fprintf(stderr, "error: %s\n", message.c_str());
	exit(EXIT_FAILURE);
}

#endif
