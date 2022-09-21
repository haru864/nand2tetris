#include <iostream>
#include <string.h>
#include <stdlib.h>

char *getFileName(char *);

int main()
{
    // char *s = "abc";
    // char s[] = "abc";
    // fprintf(stdout, "%lu\n", sizeof(s) / sizeof(char));
    // fprintf(stdout, "%lu\n", strlen(s));
    // for (int i = 0; i < sizeof(s) / sizeof(char); i++)
    // {
    //     fprintf(stdout, "i:%d %c %d\n", i, s[i], (int)s[i]);
    // }

    // char *filepath = "/home/sample.asm";
    // char *filename = getFileName(filepath);
    // for (int i = 0; filename[i] != '\0'; i++)
    // {
    //     std::cout << filename[i];
    // }
    // std::cout << std::endl;
    // std::cout << strlen(filename) << std::endl;

    int *pointer = (int *)malloc(8); // メモリ確保
    free(pointer);                   // メモリ解放

    pointer;       // ダングリングポインタ
    // free(pointer); // ダングリングポインタへの二重解放はクラッシュ（危険）

    pointer = NULL; // ダングリングポインタの影響を回避
    free(pointer);  // 空ポインタへの二重解放は無効化（安全）
    *pointer = 99;  // 空ポインタへの操作はクラッシュ（セキュリティリスクの回避）

    return 0;
}

char *getFileName(char *filepath)
{
    int p = 0;
    std::string s(filepath);

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '/')
        {
            p = i;
        }
    }

    char *filename = (char *)malloc(strlen(filepath) - p);
    filename = &filepath[p + 1];

    return filename;
}