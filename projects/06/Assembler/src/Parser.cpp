#include "../include/Parser.h"

Parser::Parser(std::string path)
{
    // std::cout << "Parser started..." << std::endl;
    Parser::asmFile = fopen(path.c_str(), "r");
    if (!Parser::asmFile)
    {
        perror("invalid file name");
        exit(1);
    }
}

Parser::~Parser()
{
    // std::cout << "Parser ended" << std::endl;
    fclose(asmFile);
}

bool Parser::hasMoreCommands()
{
    // fprintf(stderr, "%p, %p\n", asmFile->_IO_read_ptr, asmFile->_IO_read_end);
    // fprintf(stderr, "%d\n", feof(asmFile));
    return (feof(asmFile) == 0) ? true : false;
}

void Parser::advance()
{
    char buf[BUF_SIZE];
    while (fgets(buf, BUF_SIZE, Parser::asmFile) != NULL)
    {
        if (buf[0] == '\n' || (buf[0] == '/' && buf[1] == '/'))
        {
            continue;
        }
        else
        {
            break;
        }
    }
    Parser::currentCommand = "";
    for (int i = 0; i < BUF_SIZE; i++)
    {
        if (buf[i] == '\n' || buf[i] == '\0' || (buf[i] == '/' && buf[i + 1] == '/'))
        {
            break;
        }
        if (buf[i] == ' ')
        {
            continue;
        }
        // fprintf(stdout, "%d\n", (int)buf[i]);
        Parser::currentCommand += buf[i];
    }
}

int Parser::commandType()
{
    if (currentCommand[0] == '@')
    {
        return A_COMMAND;
    }
    else if (currentCommand[0] == '(')
    {
        return L_COMMAND;
    }
    else if (currentCommand.find("=") != std::string::npos ||
             currentCommand.find(";") != std::string::npos)
    {
        return C_COMMAND;
    }
    return -1;
}

std::string Parser::symbol()
{
    if (currentCommand[0] == '@')
    {
        return currentCommand.substr(1);
    }
    else if (currentCommand[0] == '(')
    {
        return currentCommand.substr(1, currentCommand.length() - 2);
    }
    return "";
}

std::string Parser::dest()
{
    auto pos = currentCommand.find("=");
    if (pos != std::string::npos)
    {
        return currentCommand.substr(0, pos);
    }
    return "";
}

std::string Parser::comp()
{
    auto head = currentCommand.find("=");
    auto tail = currentCommand.find(";");
    if (head == std::string::npos)
    {
        head = -1;
    }
    if (tail == std::string::npos)
    {
        tail = currentCommand.length();
        // printf("cmd: %s, %d\n", currentCommand.c_str(), (int)currentCommand.length());
    }
    head++;
    return currentCommand.substr(head, tail - head);
}

std::string Parser::jump()
{
    auto pos = currentCommand.find(";");
    if (pos != std::string::npos)
    {
        return currentCommand.substr(pos + 1);
    }
    return "";
}
