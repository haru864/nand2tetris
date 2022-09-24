#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <limits.h>
#include <map>

#define INSTRUCTION_SIZE 16

#define SAFE_FREE(ptr) \
    {                  \
        free(ptr);     \
        ptr = NULL;    \
    }

typedef struct FILE_WITH_NAME
{
    FILE *fileptr;
    char *name;
} file_with_name;

std::map<std::string, std::string> COMP_TABLE, DEST_TABLE, JUMP_TABLE;

void initTable();
void error_exit(char *);
char *getFileName(char *);
void openOutFile(file_with_name &, char *, char *);
void do_assemble(FILE *, FILE *);
void interpret_A_instruction(char *, char *);
void interpret_C_instruction(char *, char *);
void specify_comp(char *, char *);
void specify_dest(char *, char *, int &);
void specify_jump(char *, char *);
void printChar(char *);

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        fprintf(stderr, "four argument requires: source asm (-i \"filename\") and destination hack (-o \"filename\")\n");
        exit(1);
    }

    initTable();

    file_with_name inFile, outFile;
    inFile.fileptr = NULL;
    inFile.name = NULL;
    outFile.fileptr = NULL;
    outFile.name = NULL;
    char *destDir = NULL;
    int r;

    while ((r = getopt(argc, argv, "i:o:")) != -1)
    {
        switch (r)
        {
        case 'i':
            // printChar(optarg);
            inFile.fileptr = fopen(optarg, "r");
            if (!inFile.fileptr)
            {
                error_exit("invalid filepath (-i option)");
            }
            inFile.name = getFileName(optarg);
            break;
        case 'o':
            destDir = strdup(optarg);
            if (!destDir)
            {
                error_exit("cannot specify directory (-o option)");
            }
            break;
        case '?':
            error_exit("unknown option");
            break;
        }
    }

    if (optind != argc || !inFile.fileptr || !destDir)
    {
        fprintf(stderr, "invalid argument\n");
        exit(1);
    }

    openOutFile(outFile, inFile.name, destDir);

    do_assemble(inFile.fileptr, outFile.fileptr);

    if (fclose(inFile.fileptr) == EOF)
    {
        error_exit("failure to close file(1)");
    }
    SAFE_FREE(inFile.name);
    if (fclose(outFile.fileptr) == EOF)
    {
        error_exit("failure to close file(2)");
    }
    // SAFE_FREE(outFile.name);
    SAFE_FREE(destDir);

    return 0;
}

void initTable()
{
    COMP_TABLE["0"] = "0101010";
    COMP_TABLE["1"] = "0111111";
    COMP_TABLE["-1"] = "0111010";
    COMP_TABLE["D"] = "0001100";
    COMP_TABLE["A"] = "0110000";
    COMP_TABLE["!D"] = "0001101";
    COMP_TABLE["!A"] = "0110001";
    COMP_TABLE["-D"] = "0001111";
    COMP_TABLE["-A"] = "0110011";
    COMP_TABLE["D+1"] = "0011111";
    COMP_TABLE["A+1"] = "0110111";
    COMP_TABLE["D-1"] = "0001110";
    COMP_TABLE["A-1"] = "0110010";
    COMP_TABLE["D+A"] = "0000010";
    COMP_TABLE["D-A"] = "0010011";
    COMP_TABLE["A-D"] = "0000111";
    COMP_TABLE["D&A"] = "0000000";
    COMP_TABLE["D|A"] = "0010101";
    // COMP_TABLE[] = "1101010"; // not allocated
    // COMP_TABLE[] = "1111111"; // not allocated
    // COMP_TABLE[] = "1111010"; // not allocated
    // COMP_TABLE[] = "1001100"; // not allocated
    COMP_TABLE["M"] = "1110000";
    // COMP_TABLE[] = "1001101"; // not allocated
    COMP_TABLE["!M"] = "1110001";
    // COMP_TABLE[] = "1001111"; // not allocated
    COMP_TABLE["-M"] = "1110011";
    // COMP_TABLE[] = "1011111"; // not allocated
    COMP_TABLE["M+1"] = "1110111";
    // COMP_TABLE[] = "1001110"; // not allocated
    COMP_TABLE["M-1"] = "1110010";
    COMP_TABLE["D+M"] = "1000010";
    COMP_TABLE["D-M"] = "1010011";
    COMP_TABLE["M-D"] = "1000111";
    COMP_TABLE["D&M"] = "1000000";
    COMP_TABLE["D|M"] = "1010101";

    DEST_TABLE["M"] = "001";
    DEST_TABLE["D"] = "010";
    DEST_TABLE["MD"] = "011";
    DEST_TABLE["A"] = "100";
    DEST_TABLE["AM"] = "101";
    DEST_TABLE["AD"] = "110";
    DEST_TABLE["AMD"] = "111";

    JUMP_TABLE["JGT"] = "001";
    JUMP_TABLE["JEQ"] = "010";
    JUMP_TABLE["JGE"] = "011";
    JUMP_TABLE["JLT"] = "100";
    JUMP_TABLE["JNE"] = "101";
    JUMP_TABLE["JLE"] = "110";
    JUMP_TABLE["JMP"] = "111";
}

char *getFileName(char *filepath)
{
    int p = 0;

    for (int i = 0; filepath[i] != '\0'; i++)
    {
        if (filepath[i] == '/')
        {
            p = i;
        }
    }

    char *filename = (char *)malloc(strlen(filepath) - p);
    for (int i = 0;; i++)
    {
        filename[i] = filepath[p + 1 + i];
        if (filename[i] == '\0')
        {
            break;
        }
    }

    return filename;
}

void openOutFile(file_with_name &outFile, char *inFileName, char *outFileDir)
{
    std::string temp(inFileName);
    size_t pos = temp.find(".asm");
    if (pos == std::string::npos)
    {
        fprintf(stderr, "only .asm file is processed correctly\n");
    }
    temp = temp.substr(0, pos) + ".hack";
    char *outFileName = (char *)malloc(temp.length());
    for (int i = 0; i < temp.length(); i++)
    {
        outFileName[i] = temp[i];
        if (i == temp.length() - 1)
        {
            outFileName[i + 1] = '\0';
        }
    }

    std::string outFilePath(outFileDir);
    if (outFilePath.back() != '/')
    {
        outFilePath += '/';
    }

    outFile.name = outFileName;
    // printChar(outFile.name);
    // printChar(const_cast<char *>((outFilePath + outFileName).c_str()));
    outFile.fileptr = fopen((outFilePath + outFileName).c_str(), "w");
    if (!outFile.fileptr)
    {
        error_exit("cannot open/create hack file");
    }
}

void do_assemble(FILE *in, FILE *out)
{
    char buf[LINE_MAX];

    while (fgets(buf, sizeof(buf), in))
    {
        if (buf[0] == '\n' || (buf[0] == '/' && buf[1] == '/'))
            continue;

        char binary[INSTRUCTION_SIZE + 2];
        for (int i = 0; i < INSTRUCTION_SIZE; i++)
        {
            binary[i] = '0';
        }
        binary[INSTRUCTION_SIZE] = '\n';
        binary[INSTRUCTION_SIZE + 1] = '\0';

        if (buf[0] == '@')
        {
            interpret_A_instruction(buf, binary);
        }
        else
        {
            interpret_C_instruction(buf, binary);
        }

        if (fputs(binary, out) == EOF)
        {
            fprintf(stderr, "failure to write destination file\n");
        }
    }
}

void interpret_A_instruction(char *buf, char *binary)
{
    int dec = 0;
    for (int i = 1; buf[i] != '\n'; i++)
    {
        dec = dec * 10 + (buf[i] - '0');
    }
    std::string binaryDigit = "";
    while (dec > 0)
    {
        char ch = (dec % 2) + '0';
        binaryDigit = ch + binaryDigit;
        dec /= 2;
    }
    int idx = INSTRUCTION_SIZE - binaryDigit.length();
    for (size_t i = 0; i < binaryDigit.length(); i++)
    {
        binary[idx++] = binaryDigit[i];
    }
}

void interpret_C_instruction(char *buf, char *binary)
{
    binary[0] = binary[1] = binary[2] = '1';
    char *pos_equal = strchr(buf, '=');
    char *pos_semicolon = strchr(buf, ';');
    int idx = 0;
    if (pos_equal)
    {
        specify_dest(buf, binary, idx);
        specify_comp(pos_equal + 1, binary);
    }
    if (pos_semicolon)
    {
        specify_jump(pos_semicolon + 1, binary);
        specify_comp(buf, binary);
    }
}

void specify_comp(char *buf, char *binary)
{
    std::string comp = "";
    for (int i = 0; buf[i] != '\n' && buf[i] != ';'; i++)
    {
        comp += buf[i];
    }
    // std::cout << comp << std::endl;

    for (int i = 0; i < 7; i++)
    {
        binary[3 + i] = COMP_TABLE[comp][i];
    }
}

void specify_dest(char *buf, char *binary, int &idx)
{
    std::string dest = "";

    if (buf[1] == '=')
    {
        idx = 2;
    }
    if (buf[2] == '=')
    {
        idx = 3;
    }
    if (buf[3] == '=')
    {
        idx = 4;
    }

    for (int i = 0; i < (idx - 1); i++)
    {
        dest += buf[i];
    }
    // std::cout << "dest: " << dest << std::endl;

    for (int i = 0; i < 3; i++)
    {
        binary[10 + i] = DEST_TABLE[dest][i];
    }
}

void specify_jump(char *buf, char *binary)
{
    std::string jump = "";
    for (int i = 0; i < 3; i++)
    {
        jump += buf[i];
    }
    // std::cout << "jump: " << jump << std::endl;
    for (int i = 0; i < 3; i++)
    {
        binary[13 + i] = JUMP_TABLE[jump][i];
    }
}

void error_exit(char *s)
{
    perror(s);
    exit(1);
}

void printChar(char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        fprintf(stderr, "%c", s[i]);
    }
    fprintf(stderr, "\n");
}
