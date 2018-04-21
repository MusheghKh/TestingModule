#ifndef PROCESSUTIL_H
#define PROCESSUTIL_H

#include <windows.h>
#include <stdio.h>
#include <psapi.h>

#include <QMap>

class ProcessUtil
{
public:
    ProcessUtil();

//    static void printMemoryInfo(DWORD processID );
//    static void printAllMemeoryInfo();
    static QMap<QString, QString> getProcessData(qint64 pid);
    static QString getSystemRam();
    static int getIdleCPUTime();
    static QString getAllTasks();
};

#endif // PROCESSUTIL_H
