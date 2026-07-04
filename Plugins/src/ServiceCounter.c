#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsvc.h>

static DWORD CountRunning(DWORD type)
{
    SC_HANDLE h = OpenSCManagerW(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
    if (!h)
        return 0;

    DWORD needed = 0, count = 0, resume = 0;

    /* first call fails on purpose, just to get the required buffer size */
    EnumServicesStatusExW(h, SC_ENUM_PROCESS_INFO, type, SERVICE_ACTIVE,
        NULL, 0, &needed, &count, &resume, NULL);

    if (needed)
    {
        BYTE *buf = HeapAlloc(GetProcessHeap(), 0, needed);
        if (buf)
        {
            resume = 0;
            count = 0;
            EnumServicesStatusExW(h, SC_ENUM_PROCESS_INFO, type, SERVICE_ACTIVE,
                buf, needed, &needed, &count, &resume, NULL);
            HeapFree(GetProcessHeap(), 0, buf);
        }
    }

    CloseServiceHandle(h);
    return count;
}

__declspec(dllexport) void Initialize(void **data, void *rm)
{
    *data = NULL;
}

__declspec(dllexport) void Reload(void *data, void *rm, double *maxValue)
{
    /* nothing to reload, counts are computed fresh in Update */
}

__declspec(dllexport) double Update(void *data)
{
    return (double)CountRunning(SERVICE_WIN32);
}

__declspec(dllexport) void Finalize(void *data)
{
}

BOOL WINAPI DllMain(HINSTANCE h, DWORD reason, LPVOID reserved)
{
    return TRUE;
}
