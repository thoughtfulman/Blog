//a minimum program to test how extern "C" is need in C++
#include<stdio.h>

namespace myname {
    int var = 42;
}

extern "C" int _ZN6myname3varE;

int main()
{
    printf("%d\n", _ZN6myname3varE);
    myname::var ++;
    printf("%d\n", _ZN6myname3varE);
    printf("%p\n",&_ZN6myname3varE);
    printf("%p\n", &myname::var);
    return 0;
}
