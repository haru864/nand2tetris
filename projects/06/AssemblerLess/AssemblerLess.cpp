#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <string>

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

void error_exit(char *);
char *getFileName(char *);
void getOutFile(file_with_name &, char *, char *);
void printChar(char *);

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        fprintf(stderr, "four argument requires: source asm (-i \"filename\") and destination hack (-o \"filename\")\n");
        exit(1);
    }

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

    getOutFile(outFile, inFile.name, destDir);

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

void getOutFile(file_with_name &outFile, char *inFileName, char *outFileDir)
{
    std::string temp(inFileName);
    size_t pos = temp.find(".asm");
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
