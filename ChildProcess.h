#pragma once
#include "framework.h"

class ChildProcess
{
private:
	bool ExecuteProcessAndGetOutput(LPWSTR szCmdLine, CString& strOutput);
	bool ExecuteProcessAndGetOutput(LPWSTR szCmdLine);
	WCHAR spacyPath[MAX_PATH];
	WCHAR transPath[MAX_PATH];
public:
	ChildProcess();
	bool Translate(CString str, CString& output);
	bool ExtractPart(CString str);
};

