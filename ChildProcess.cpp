#define _CRT_NON_CONFORMING_SWPRINTFS
#include "ChildProcess.h"

ChildProcess::ChildProcess() {
    WCHAR buffer[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, buffer);
    wprintf(_T("%s\n"), buffer);

    swprintf(spacyPath, LR"("%s\spacyModel.exe")", buffer);
    //spacyPath.ReleaseBuffer();

    swprintf(transPath, LR"("%s\googleTrans.exe")", buffer);
    //transPath.ReleaseBuffer();

    wprintf(L"%s\n%s\n", spacyPath, transPath);
}
bool ChildProcess::Translate(CString str, CString& output) {
    WCHAR* cmdLineBuf=new WCHAR[10000];
    bool result;

    swprintf(cmdLineBuf, LR"(%s "%s")", transPath, str);
    result = ExecuteProcessAndGetOutput(cmdLineBuf, output);

    delete[] cmdLineBuf;
    return result;
}
int ChildProcess::ExtractPart(CString str) {
    CString output;
    WCHAR* cmdLineBuf = new WCHAR[10000];
    bool result=true;

    str.Replace(L"\r\n", LR"( )");
    str.Replace(L"\"", LR"(\")");
    swprintf(cmdLineBuf, LR"(%s "%s")", spacyPath, str);
    //swprintf(cmdLineBuf, LR"(%s "hello")", spacyPath);
    //wprintf(L"%s\n", cmdLineBuf);


    result = ExecuteProcessAndGetOutput(cmdLineBuf, output);
    /*CStringA cmd(cmdLineBuf);
    system(cmd);*/
    int id = result?_wtoi(output):-1;
    printf("textid: %d\n", id);
    delete[] cmdLineBuf;
    return id;
}










bool ChildProcess::ExecuteProcessAndGetOutput(LPWSTR szCmdLine, CString& strOutput)
{
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    HANDLE hReadPipe, hWritePipe;
    if (!CreatePipe(&hReadPipe, &hWritePipe, &saAttr, 0))
        return FALSE;

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = hWritePipe;
    si.hStdError = hWritePipe;

    //wprintf(L"szCmdLine: %s\n", szCmdLine);

    if (!CreateProcess(NULL, szCmdLine, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        CloseHandle(hReadPipe);
        CloseHandle(hWritePipe);
        return FALSE;
    }

    CloseHandle(hWritePipe);

    char buffer[4096];
    DWORD dwRead;
    while (ReadFile(hReadPipe, buffer, sizeof(buffer), &dwRead, NULL) && dwRead != 0)
    {
        buffer[dwRead] = '\0';
        strOutput += buffer;
    }

    CloseHandle(hReadPipe);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);


    return TRUE;
}

bool ChildProcess::ExecuteProcessAndGetOutput(LPWSTR szCmdLine)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;

    //wprintf(L"szCmdLine: %s\n", szCmdLine);

    if (!CreateProcess(NULL, szCmdLine, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        return FALSE;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return TRUE;
}
