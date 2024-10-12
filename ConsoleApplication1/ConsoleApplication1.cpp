// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>


#if defined(_WIN32)
#define PathToLibrary "C:/Users/gatesgao/RiderProjects/NativeLibrary/bin/pub/NativeLibrary.dll"
#elif defined(__APPLE__)
#define PathToLibrary "NativeLibrary.dylib"
#else
#define PathToLibrary "NativeLibrary.so"
#endif

#ifdef _WIN32
#include "windows.h"
#define symLoad GetProcAddress
#pragma comment (lib, "ole32.lib")
#else
#include "dlfcn.h"
#include <unistd.h>
#define symLoad dlsym
#define CoTaskMemFree free
#endif

#include <stdlib.h>
#include <stdio.h>

#ifndef F_OK
#define F_OK    0
#endif

#pragma comment(lib, "NativeLibrary.lib")
//#pragma comment(lib, "bootstrapperdll.obj")
#pragma comment(lib, "System.Globalization.Native.Aot.lib")
#pragma comment(lib, "System.IO.Compression.Native.Aot.lib")
#pragma comment(lib, "Runtime.VxsortEnabled.lib")
#pragma comment(lib, "Runtime.WorkstationGC.lib")
#pragma comment(lib, "eventpipe-enabled.lib")

#pragma comment(lib, "ncrypt.lib")
//#pragma comment(lib, "Bcrypt.lib")




int callSumFunc(const char* path, const char* funcName, int a, int b);
char* callSumStringFunc(const char* path, const char* funcName, const  char* firstString,const  char* secondString);

typedef  const char* (*CppSumImpl)(char* input);

void callSetCppSumFunc(const char* path, const char* funcName,  CppSumImpl func);

extern "C" {
    void sayhello(const char* words);
    void  SetCppFunc(CppSumImpl x);
    char* aotsample_sumstring(const char* a, const char* b);
    const char* CPPsumstring(const char* words);
}


std::string GLobalStr;

const char* CppAdd(char* input)
{
    printf("CppAdd call  is %s \n", input);
    GLobalStr = ":: CppAddnow";
    GLobalStr += input;

    return GLobalStr.c_str();
}

const char* CPPsumstring(const char* words)
{
    GLobalStr = words;
    GLobalStr += " CPPsumstring";
    return GLobalStr.c_str();
}



int main()
{
    // Check if the library file exists
    //if (access(PathToLibrary, F_OK) == -1)
   // {
    //    puts("Couldn't find library at the specified path");
    //    return 0;
    //}

    // Sum two integers
    //int sum = callSumFunc(PathToLibrary, "aotsample_add", 2, 8);
    //printf("The sum is %d \n", sum);

    sayhello("cpp call");

   // callSetCppSumFunc(PathToLibrary, "SetCppFunc", CppAdd);
    SetCppFunc(CppAdd);
    // Concatenate two strings
    //char* sumstring = callSumStringFunc(PathToLibrary, "aotsample_sumstring", "ok", "ko");
    char* sumstring = aotsample_sumstring("ok", "ko");

    printf("The concatenated string is %s \n", sumstring);

    // Free string
    //CoTaskMemFree(sumstring);
}

int callSumFunc(const char* path, const char* funcName, int firstInt, int secondInt)
{
    // Call sum function defined in C# shared library
#ifdef _WIN32
    HINSTANCE handle = LoadLibraryA(path);
#else
    void* handle = dlopen(path, RTLD_LAZY);
#endif

    typedef int(*myFunc)(int, int);
    myFunc MyImport = (myFunc)symLoad(handle, funcName);

    int result = MyImport(firstInt, secondInt);

    // NOTE: Native AOT libraries do not support unloading
    return result;
}

void callSetCppSumFunc(const char* path, const char* funcName , CppSumImpl func)
{
    #ifdef _WIN32
        HINSTANCE handle = LoadLibraryA(path);
    #else
        void* handle = dlopen(path, RTLD_LAZY);
    #endif

        typedef void(*myFunc)(CppSumImpl);
        myFunc MyImport = (myFunc)symLoad(handle, funcName);
        MyImport(func);
}


char* callSumStringFunc(const char* path, const char* funcName,  const char* firstString, const char* secondString)
{
    // Library loading
#ifdef _WIN32
    HINSTANCE handle = LoadLibraryA(path);
#else
    void* handle = dlopen(path, RTLD_LAZY);
#endif

    // Declare a typedef
    typedef char* (*myFunc)(const char*, const char*);

    // Import Symbol named funcName
    myFunc MyImport = (myFunc)symLoad(handle, funcName);

    // The C# function will return a pointer
    char* result = MyImport(firstString, secondString);

    // CoreRT libraries do not support unloading
    // See https://github.com/dotnet/corert/issues/7887
    return result;
}


//int main()
//{
//    std::cout << "Hello World!\n";
//}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
