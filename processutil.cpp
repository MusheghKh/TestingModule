#include "processutil.h"

#include <QDebug>
#include <QProcess>
#include <sstream>

// tasklist /fo LIST /v /FI "pid eq 1112" example command for task info

ProcessUtil::ProcessUtil()
{

}

//void ProcessUtil::printMemoryInfo(DWORD processID)
//{
//        HANDLE hProcess;
//        PROCESS_MEMORY_COUNTERS pmc;

//        // Print the process identifier.

//        qDebug() << QString( "Process ID: %1").arg(processID );

//        // Print information about the memory usage of the process.

//        hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID );
//        if (NULL == hProcess)
//        {
//            return;
//        }

//        if ( GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc)) )
//        {
//            qDebug() << QString( "PageFaultCount: 0x%08X").arg(pmc.PageFaultCount, 8, 10, QLatin1Char('0'));
//            qDebug() << QString( "PeakWorkingSetSize: 0x%08X").arg(pmc.PeakWorkingSetSize );
//            qDebug() << QString( "WorkingSetSize: 0x%08X").arg(pmc.WorkingSetSize );
//            qDebug() << QString( "QuotaPeakPagedPoolUsage: 0x%08X").arg(pmc.QuotaPeakPagedPoolUsage );
//            qDebug() << QString( "QuotaPagedPoolUsage: 0x%08X").arg(pmc.QuotaPagedPoolUsage );
//            qDebug() << QString( "QuotaPeakNonPagedPoolUsage: 0x%08X").arg(pmc.QuotaPeakNonPagedPoolUsage );
//            qDebug() << QString( "QuotaNonPagedPoolUsage: 0x%08X").arg(pmc.QuotaNonPagedPoolUsage );
//            qDebug() << QString( "PagefileUsage: 0x%08X").arg(pmc.PagefileUsage );
//            qDebug() << QString( "PeakPagefileUsage: 0x%08X").arg(pmc.PeakPagefileUsage );
//        }
//        qDebug() << QString("#######################################################################################");

//        CloseHandle( hProcess );
//}

//void ProcessUtil::printAllMemeoryInfo()
//{
//    // Get the list of process identifiers.

//    DWORD aProcesses[1024], cbNeeded, cProcesses;
//    unsigned int i;

//    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
//    {
//        return;
//    }

//    // Calculate how many process identifiers were returned.

//    cProcesses = cbNeeded / sizeof(DWORD);

//    // Print the memory usage for each process

//    qDebug() << QString("count: " + cProcesses);

//    for ( i = 0; i < cProcesses; i++ )
//    {
//        ProcessUtil::printMemoryInfo( aProcesses[i] );
//    }
//}

QMap<QString, QString> ProcessUtil::getProcessData(qint64 pid){
    QMap<QString, QString> result;
    QString command = QString("tasklist /v /fo LIST /fi \"pid eq %1\"").arg(pid);
    QProcess cmd;
    cmd.start(command);
    cmd.waitForFinished(-1);
    QTextStream out(cmd.readAllStandardOutput());
    while(!out.atEnd()){
        bool readKey = true;
        std::stringstream key("");
        std::stringstream val("");
        QString line = out.readLine();
        for(int i = 0; i < line.length(); i++){
            if(line[i] == ' '){
                continue;
            }
            if(readKey){
                if(line[i] == ':'){
                    readKey = false;
                    continue;
                }
                key << line[i].toLatin1();
            }else {
                val << line[i].toLatin1();
            }
        }
        QString k = QString::fromStdString(key.str());
        QString v = QString::fromStdString(val.str());
        result.insert(k, v);
        qDebug() << k;
        qDebug() << v;
        qDebug() << line;
    }
    return result;
}

// in MB
QString ProcessUtil::getSystemRam(){
    MEMORYSTATUSEX memory_status;
    ZeroMemory(&memory_status, sizeof(MEMORYSTATUSEX));
    memory_status.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memory_status)) {
        QString result = QString("%1")
                .arg(memory_status.ullTotalPhys / (1024 * 1024));
        qDebug() << result;
        return result;
    } else {
        return "Unknown";
    }
}
