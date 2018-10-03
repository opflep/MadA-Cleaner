// NoName Cleaner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pefile.h"

HANDLE getInflectedProcess();
int main()
{
	UpdatePrivilege();
	getInflectedProcess();
    return 0;
}

HANDLE getInflectedProcess() {
	HANDLE hProcessSnap;
	HANDLE hProcess;
	MODULEENTRY32 me32;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	me32.dwSize = sizeof(MODULEENTRY32);
	hProcessSnap = CreateToolhelp32Snapshot(2, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE){
		std::cout<< "CreateToolhelp32Snapshot of processes";
		return(FALSE);
	}
	Process32First(hProcessSnap, &pe32);
	
	_tprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile);
	std::cout << "xxx";
	do {
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		//printf("%d", GetLastError());
		Process32Next(hProcessSnap, &pe32);
		Module32First(hProcess, &me32);
	} while (hProcess == 0);
	do {
		
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		int a = GetLastError();
		if (hProcess == 0) {
			//printf("%d", GetLastError());
		}
		else {
			char *p = NULL;
			unsigned int start, end;
			DWORD read;
			MEMORY_BASIC_INFORMATION mbi;
			VirtualQueryEx(hProcess, p, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
			int a = GetLastError();
			/*start = (unsigned)mbi.BaseAddress;
			end = (unsigned)mbi.BaseAddress + mbi.RegionSize;

			LPBYTE buffer = new BYTE[end - start];

			if (ReadProcessMemory(hProcess, p, buffer, end - start, &read) == NULL) {
				std::cout << "Out"<<GetLastError();
			}
			else {
				std::cout << "Yes";
			}*/
		}
	} while (Process32Next(hProcessSnap, &pe32));

	


//	while (Process32Next(hProcessSnap, &pe32)) {
//		_tprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile);
//	}

	getchar();

}
