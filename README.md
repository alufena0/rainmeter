Custom Rainmeter plugins and skin for monitoring my system. Vibe coded with AI assistance.

## Plugins

| Plugin | Description |
| --- | --- |
| [ServiceCounter](./Plugins/src/ServiceCounter.c) | Counts how many Windows services are currently running |
| [DriverCounter](./Plugins/src/DriverCounter.c) | Counts how many kernel/filesystem drivers are currently running |

Both are native x64 DLLs, no .NET, no external dependencies beyond `kernel32.dll` and `advapi32.dll`. They call `EnumServicesStatusExW` from the Windows Service Control Manager API, filtered by service type (`SERVICE_WIN32` vs `SERVICE_DRIVER`).

`PerfMon.dll` is the official Rainmeter plugin (not mine), used in the skin for the process count.  
Docs: https://docs.rainmeter.net/manual/plugins/deprecated/perfmon/

https://www.virustotal.com/gui/file/d0d16fe303d9deaeadab907292e3526b5533add33ba09e4ecf703a353b75b6d6/detection  
https://www.virustotal.com/gui/file/96837b9046080161ab71a1b38b4e465c39dc462cb84498a42a846e073b264b5e/detection  
https://www.virustotal.com/gui/file/0c318e848cbb4fe0f973dbae3b89b0900cdcfcbe94aa1119a140d1a21edccbd0/detection

## Skin
[Skins/Processes/Process.ini](./Skins/Processes/Process.ini) shows three rows: processes, services, drivers, all running counts.

<img width="132" height="45" alt="Untitled" src="https://github.com/user-attachments/assets/27377c4f-4128-45e0-82b2-fa861eb39b42" />

## Installation
Copy `Plugins/*.dll` to `Rainmeter/Plugins/`, copy `Skins/Processes/` to `Rainmeter/Skins/`, load the skin.

## Building
MinGW-w64, no CRT bloat, symbols stripped:

```
x86_64-w64-mingw32-gcc -O2 -shared -static -s -o ServiceCounter.dll ServiceCounter.c -lkernel32 -ladvapi32
x86_64-w64-mingw32-gcc -O2 -shared -static -s -o DriverCounter.dll DriverCounter.c -lkernel32 -ladvapi32
```
