#include "summoner.h"

#include <Windows.h>
#include <windows.h>
#include <ntstatus.h>
#include <TlHelp32.h>
#include <Winternl.h>
#include <ntstatus.h>
#include <Psapi.h>
#include <string>
#include <iostream> 
#include <Shlwapi.h>
#define SYSTEMHANDLEINFORMATION 16
#pragma comment(lib, "ntdll.lib")

using namespace std;

unsigned long get_module(unsigned long pid, char* module_name, unsigned long *size) {
	
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;

	//  Take a snapshot of all modules in the specified process. 
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, (DWORD)pid);
	if (hModuleSnap == INVALID_HANDLE_VALUE){
		cout << GetLastError() << endl;
		return NULL;
	}
	me32.dwSize = sizeof(MODULEENTRY32);

	if (!Module32First(hModuleSnap, &me32))
	{
		CloseHandle(hModuleSnap);     // Must clean up the snapshot object! 
		return NULL;
	}
	do {
		wstring ws(me32.szModule);
		string str(ws.begin(), ws.end());
		if (strcmp(str.c_str(), module_name) == 0) {
			CloseHandle(hModuleSnap);
			return (unsigned long)me32.modBaseAddr;
		}
	} while ((Module32Next(hModuleSnap, &me32)));

	CloseHandle(hModuleSnap);
	return NULL;
}

void command_buff(HWND hwnd) {
	Sleep(300);

	PostMessage(hwnd, WM_KEYDOWN, VK_RETURN, MapVirtualKey(VK_RETURN, MAPVK_VK_TO_VSC));
	PostMessage(hwnd, WM_KEYUP, VK_RETURN, MapVirtualKey(VK_RETURN, MAPVK_VK_TO_VSC));

	Sleep(50);
	PostMessage(hwnd, WM_KEYDOWN, VK_UP, MapVirtualKey(VK_UP, MAPVK_VK_TO_VSC));
	PostMessage(hwnd, WM_KEYUP, VK_UP, MapVirtualKey(VK_UP, MAPVK_VK_TO_VSC));

	Sleep(100);
	PostMessage(hwnd, WM_KEYDOWN, VK_RETURN, MapVirtualKey(VK_RETURN, MAPVK_VK_TO_VSC));
	PostMessage(hwnd, WM_KEYUP, VK_RETURN, MapVirtualKey(VK_RETURN, MAPVK_VK_TO_VSC));

}

void F2_buff(HWND hwnd) {
	Sleep(300);
	for (int n = 0; n < 5; n++) {
		Sleep(20);
		PostMessage(hwnd, WM_KEYDOWN, 0x71, MapVirtualKey(0x71, MAPVK_VK_TO_VSC));
		Sleep(40);
		PostMessage(hwnd, WM_KEYUP, 0x71, MapVirtualKey(0x71, MAPVK_VK_TO_VSC));
	}
}

void F3_buff(HWND hwnd) {
	Sleep(300);
	PostMessage(hwnd, WM_KEYDOWN, 0x72, MapVirtualKey(0x72, MAPVK_VK_TO_VSC));
	Sleep(40);
	PostMessage(hwnd, WM_KEYUP, 0x72, MapVirtualKey(0x72, MAPVK_VK_TO_VSC));
}

void F4_buff(HWND hwnd) {
	Sleep(300);
	PostMessage(hwnd, WM_KEYDOWN, 0x73, MapVirtualKey(0x73, MAPVK_VK_TO_VSC));
	Sleep(100);
	PostMessage(hwnd, WM_KEYUP, 0x73, MapVirtualKey(0x73, MAPVK_VK_TO_VSC));
}

void F5_buff(HWND hwnd) {
	Sleep(300);
	PostMessage(hwnd, WM_KEYDOWN, 0x74, MapVirtualKey(0x74, MAPVK_VK_TO_VSC));
	Sleep(100);
	PostMessage(hwnd, WM_KEYUP, 0x74, MapVirtualKey(0x74, MAPVK_VK_TO_VSC));
}

void F6_buff(HWND hwnd) {
	Sleep(300);
	PostMessage(hwnd, WM_KEYDOWN, 0x75, MapVirtualKey(0x75, MAPVK_VK_TO_VSC));
	Sleep(100);
	PostMessage(hwnd, WM_KEYUP, 0x75, MapVirtualKey(0x75, MAPVK_VK_TO_VSC));
}

void F7_buff(HWND hwnd) {
	Sleep(300);
	PostMessage(hwnd, WM_KEYDOWN, 0x76, MapVirtualKey(0x76, MAPVK_VK_TO_VSC));
	Sleep(100);
	PostMessage(hwnd, WM_KEYUP, 0x76, MapVirtualKey(0x76, MAPVK_VK_TO_VSC));
}

void all_buff(HWND hwnd) {
	Sleep(100);
	command_buff(hwnd);
	Sleep(100);
	F2_buff(hwnd);
	Sleep(100);
	F3_buff(hwnd);
	Sleep(100);
	F4_buff(hwnd);
	Sleep(100);
	F5_buff(hwnd);
	Sleep(100);
	F6_buff(hwnd);
}

void attack(HWND hwnd) {
	Sleep(100);
	PostMessage(hwnd, WM_KEYDOWN, 0x70, MapVirtualKey(0x70, MAPVK_VK_TO_VSC));
	Sleep(100);
	PostMessage(hwnd, WM_KEYUP, 0x70, MapVirtualKey(0x70, MAPVK_VK_TO_VSC));
}

void rotate_map(HWND hwnd) {
	Sleep(20);
	PostMessage(hwnd, WM_KEYDOWN, VK_RIGHT, MapVirtualKey(VK_RIGHT, MAPVK_VK_TO_VSC));
	Sleep(20);
	PostMessage(hwnd, WM_KEYUP, VK_RIGHT, MapVirtualKey(VK_RIGHT, MAPVK_VK_TO_VSC));
}

void cancel_target(HWND hwnd) {
	Sleep(100);
	PostMessage(hwnd, WM_KEYDOWN, VK_ESCAPE, MapVirtualKey(VK_ESCAPE, MAPVK_VK_TO_VSC));
	Sleep(40);
	PostMessage(hwnd, WM_KEYUP, VK_ESCAPE, MapVirtualKey(VK_ESCAPE, MAPVK_VK_TO_VSC));
}

void aoe_attack(HWND hwnd) {
	Sleep(100);
	PostMessage(hwnd, WM_KEYDOWN, 0x78, MapVirtualKey(0x78, MAPVK_VK_TO_VSC));
	Sleep(40);
	PostMessage(hwnd, WM_KEYUP, 0x78, MapVirtualKey(0x78, MAPVK_VK_TO_VSC));
}

float math::sqrt(float number){
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long *)&y;                       // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);               
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y));   // 1st iteration
										   //	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}
