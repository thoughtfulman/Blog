## extern "C"的作用
在C++引用lua的头文件时，我们总会写成：

```c++
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
```
为什么要这么做呢？原因是C++的编译器会对程序中符号进行修饰，这个过程在编译器中叫符号修饰（Name Decoration）或者符号改编（Name Mangling）。

同时我们知道C++是能够兼容C的，如果我们有了一个C语言的头文件和其对于的库，在C++中如何使用它呢？在include该头文件的时候当然要加入extern "C"，否则按照C++的符号进行符号修饰，那么在库中就会找不到该符号了。

为了加深印象，再看一个例子：
```c++
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
```
编译执行结果：
```
$:~/blog/lua$ g++ extern_c.cc
$:~/blog/lua$ ./a.out
42
43
0x601040
0x601040


```
在这个例子中，我们根据g++编译器的符号修饰规则，仿造了一个C变量（gcc不进行符号修饰），欺骗了编译器，把myname::var 和 _ZN6myname3varE当成了同一个变量了。这怎么有点像是c++中的引用？这里还是有些不是很理解。

还有另外一个问题，C语言不支持extern "C"语法，如果我们想写一个头文件，同时支持被C和C++引用，该怎么办？可以使用C++的宏 "__cplusplus"来判断是不是C++编译器。
```c++
#ifdef __cplusplus
extern "C" {
#endif

// 正式定义。。。

#ifdef __cplusplus
}
#endif

```

--<cite>程序员的自我修养：链接、装载与库/俞甲子，石凡，潘爱民著。——北京：电子工业出版社，2009.4 ISBN 978-7-121-08511-6 <cite>
