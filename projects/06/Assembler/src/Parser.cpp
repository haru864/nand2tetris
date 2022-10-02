#include "Parser.h"

Parser::Parser(std::string path)
{
    std::cout << "Parser started..." << std::endl;
    Parser::asmFile = fopen(path.c_str(), "r");
    if (!Parser::asmFile)
    {
        perror("invalid file name");
        exit(1);
    }
}

Parser::~Parser()
{
    std::cout << "Parser ended" << std::endl;
}

bool Parser::hasMoreCommands()
{
    if (Parser::asmFile->_IO_read_ptr == NULL)
    {
        return true;
    }
    return Parser::asmFile->_IO_read_ptr == Parser::asmFile->_IO_read_end;
}

void Parser::advance()
{
    while (fgets(Parser::buf, BUF_SIZE, Parser::asmFile) != NULL)
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
        if (buf[i] == '\0')
        {
            break;
        }
        Parser::currentCommand += Parser::buf[i];
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
    else if (currentCommand.find("=") == std::string::npos ||
             currentCommand.find(";") == std::string::npos)
    {
        return C_COMMAND;
    }
    return -1;
}

std::string Parser::symbol()
{
    if (currentCommand[0] != '@')
    {
        return currentCommand.substr(1);
    }
    else if (currentCommand[0] != '(')
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
    head++;
    if (tail == std::string::npos)
    {
        tail = currentCommand.length();
    }
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
