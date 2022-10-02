#include <iostream>
#include <stdio.h>
#include <map>
#include "sample.h"

using namespace std;

int main(void)
{
    // cout << MyHelper::Add(12, 13) << endl;

    // FILE *f = fopen("TestFile", "r");
    // fprintf(stdout, "%d\n", f->_IO_read_ptr == NULL);
    // fprintf(stdout, "%d\n", f->_IO_read_ptr == f->_IO_read_end);
    // fprintf(stdout, "%p\n", f->_IO_read_ptr);
    // fprintf(stdout, "%p\n", f->_IO_read_end);

    // char buf[128];
    // while (fgets(buf, sizeof(buf), f) != NULL)
    // {
    //     fprintf(stdout, buf);
    //     fprintf(stdout, "%c, %p\n", *(f->_IO_read_ptr), f->_IO_read_ptr);
    //     fprintf(stdout, "%c, %p\n", *(f->_IO_read_end), f->_IO_read_end);
    // }

    // fprintf(stdout, "%c, %p\n", *(f->_IO_read_ptr), f->_IO_read_ptr);
    // fprintf(stdout, "%c, %p\n", *(f->_IO_read_end), f->_IO_read_end);
    // fclose(f);

    // char cary[5];
    // cary[0] = 'A';
    // cary[1] = 'B';
    // cout << sizeof(cary) << endl;
    // std::string str(cary, 9);
    // cout << str << endl;
    // cout << str.length() << endl;

    map<std::string, int> m;
    m[""] = 0;
    m["1"] = 100;
    m["2"] = 200;
    cout << m[""] << endl;
    cout << m["1"] << endl;

    return 0;
}