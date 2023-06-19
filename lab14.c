#include <windows.h>
#include <tchar.h>	
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <stdarg.h>

VOID ReportError(LPCTSTR UserMessage, DWORD ExitCode, BOOL PrintErrorMsg)
{
    DWORD eMsgLen, LastErr = GetLastError();
    printf("%s\n; %d\n", UserMessage, ExitCode);

}

VOID ReportException(LPCUTSTR UserMessage, DWORD ExceptionCode)
{
    ReportError(UserMessage, ExceptionCode, TRUE);
    if (ExceptionCode != 0) RaiseException((0x0FFFFFFF & ExceptionCode) | 0xE0000000, 0, 0, NULL);
    return;
}

static BOOL WINAPI Handler(DWORD CtrlEvent);
volatile static BOOL Exit = FALSE;

int _tmain(int argc, LPTSTR argv[])
{
    if (!SetConsoleCtrlHandler(Handler, TRUE))
        ReportError(_T("Event handler error"), 1, TRUE);
    while (!Exit)
    {
        Sleep(5);
        Beep(1000, 250);
    }
    _tprintf(_T("Termination of program execution on demand\n"));
    return 0;
}

BOOL WINAPI Handler(DWORD CtrlEvent)
{
    Exit = TRUE;
    switch (CtrlEvent) {
    case CTRL_C_EVENT:
        _tprintf(_T(" Ctrl - c signal received.Exit handler after 10 seconds \n"));
        Sleep(5000);
        _tprintf(_T("Exit handler after 6 seconds"));
        Sleep(6000);
        return TRUE;

    default:
        _tprintf(_T("Event: %d. Exit handler after 10 seconds"), CtrlEvent);
        Sleep(4000);
        _tprintf(_T("Exit handler after 6 seconds"));
        Sleep(6000);
        return TRUE;
    }

}