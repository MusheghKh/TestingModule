#ifndef PROCESSUTIL_H
#define PROCESSUTIL_H

#include <windows.h>
#include <stdio.h>
#include <psapi.h>

class ProcessUtil
{
public:
    ProcessUtil();

    static void printMemoryInfo(DWORD processID );
    static void printAllMemeoryInfo();
};

#endif // PROCESSUTIL_H
