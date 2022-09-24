#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    FILE *f = fopen("in/Add.asm", "r");
    printf("%d\n", f->_fileno);
    char buf[256];

    char c;
    while (fgets(buf, sizeof(buf), f))
    {
        printf("%s", buf);
    }
    // else
    // {
    //     printf("fail to read\n");
    //     fclose(f);
    // }

    fclose(f);

    return 0;
}
