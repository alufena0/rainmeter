Custom Rainmeter plugins and skin for monitoring my system. Vibe coded with AI assistance.

## Plugins

| Plugin | Description |
| --- | --- |
| [ServiceCounter](./Plugins/src/ServiceCounter.c) | Counts how many Windows services are currently running |
| [DriverCounter](./Plugins/src/DriverCounter.c) | Counts how many kernel/filesystem drivers are currently running |

Both are native x64 DLLs, no .NET, no external dependencies beyond `kernel32.dll` and `advapi32.dll`. They call `EnumServicesStatusExW` from the Windows Service Control Manager API, filtered by service type (`SERVICE_WIN32` vs `SERVICE_DRIVER`).

`PerfMon.dll` is the official Rainmeter plugin (not mine), used in the skin for the process count. Docs: https://docs.rainmeter.net/manual/plugins/deprecated/perfmon/

## Skin
[Skins/Processes/Process.ini](./Skins/Processes/Process.ini) shows three rows: processes, services, drivers, all running counts.

## Installation
Copy `Plugins/*.dll` to `Rainmeter/Plugins/`, copy `Skins/Processes/` to `Rainmeter/Skins/`, load the skin.

## Building
MinGW-w64, no CRT bloat, symbols stripped:

```
x86_64-w64-mingw32-gcc -O2 -shared -static -s -o ServiceCounter.dll ServiceCounter.c -lkernel32 -ladvapi32
x86_64-w64-mingw32-gcc -O2 -shared -static -s -o DriverCounter.dll DriverCounter.c -lkernel32 -ladvapi32
```
