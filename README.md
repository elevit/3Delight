# 3Delight-style License Workflow Demo

This Windows C++17 sample demonstrates floating-license concepts: a fixed seat
pool, checkout tokens, denial when the pool is exhausted, check-in, and retry.

This is an educational in-memory simulation. It does not use, reproduce, bypass,
or claim compatibility with 3Delight's real licensing system. 3Delight is a
trademark of its respective owner.

## Build with Visual Studio 2022

Install the **Desktop development with C++** workload and CMake. In Developer
PowerShell for Visual Studio, run:

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\license_demo.exe
```

For Ninja:

```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
.\build\license_demo.exe
```

The first two workstations receive the available seats and the third is denied.
After a seat is checked in, the third workstation retries successfully.

