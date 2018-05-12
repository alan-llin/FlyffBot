#include "summoner.h"
#include "flyff.h"
#include "GetHandle.hpp"

#include <iostream> 
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
#include <windows.h>
#include <Windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <string.h>
#include <fcntl.h> // for the console stuff
#include <io.h> //
#include <TlHelp32.h> // for the module operations

using namespace std;

int main() {

	HWND hwnd = FindWindowA(0, "Removed :)");
	if (hwnd) {

		unsigned long pid;
		GetWindowThreadProcessId(hwnd, &pid);

		HANDLE hGame = GetHandleIdTo(L"Neuz.exe", GetCurrentProcessId());
		cout << "Handle to target: 0x" << hex << hGame << endl;

		unsigned long base_addr = 0;
		//unsigned long select_addr = 0;
		//unsigned long maxinview_addr = 0;
		//unsigned long targetbase_addr = 0;

		base_addr = get_module(pid, "Neuz.exe");
		//select_addr = base_addr + 0x494E58;
		//maxInView_addr = base_addr + 0x609770;
		//targetBase_addr = base_addr + 0x604950;

		if (WriteProcessMemory(hGame, (LPVOID)(base_addr + 0x22BC2E), "\x90\x90", 2, 0)) {
			cout << "Range Enabled" << endl;
		}

		cout << "Base_addr: " << base_addr << endl;
		cout << endl;

		flyff f(hGame, base_addr);
		f.select(0);

		all_buff(hwnd);

		Sleep(100);
		clock_t initial_time_command = clock();
		clock_t initial_time_F3 = clock();
		clock_t initial_time_F4 = clock();
		clock_t initial_time_F5 = clock();
		clock_t initial_time_F6 = clock();

		for (;; Sleep(20)) {
			clock_t current_time = clock();
			float command_difference = ((float)current_time - initial_time_command) / CLOCKS_PER_SEC;
			float F3_difference = ((float)current_time - initial_time_F3) / CLOCKS_PER_SEC;
			float F4_difference = ((float)current_time - initial_time_F4) / CLOCKS_PER_SEC;
			float F5_difference = ((float)current_time - initial_time_F5) / CLOCKS_PER_SEC;
			float F6_difference = ((float)current_time - initial_time_F6) / CLOCKS_PER_SEC;
			if (command_difference > 3700) {
				command_buff(hwnd);
				initial_time_command = clock();
			}
			if (F3_difference > (float)1800.0) {
				F3_buff(hwnd);
				F2_buff(hwnd);
				initial_time_F3 = clock();
			}
			if (F4_difference > (float)780.0) {
				F4_buff(hwnd);
				initial_time_F4 = clock();
			}
			if (F5_difference > (float)600.0) {
				F5_buff(hwnd);
				initial_time_F5 = clock();
			}
			if (F6_difference > (float)240.0) {
				F6_buff(hwnd);
				initial_time_F6 = clock();
			}
			if (f.getSelect() == 0) {
				flyff::targetInfo ti = f.getClosestTargetInView();
				if (ti.base != 0) {
					string hex_lvl = "0x" + std::to_string(ti.lvl);
					string hex_hp = "0x" + std::to_string(ti.hp);
					unsigned long long_lvl = stoul(hex_lvl, nullptr, 16);
					unsigned long long_hp = stoul(hex_hp, nullptr, 16);

					cout << "Select closest target:" << endl;
					cout << "--Name: " << ti.name << endl;
					cout << "--Level: " << long_lvl << endl;
					cout << "--HP: " << long_hp << endl;
					cout << "--Hyp: " << ti.hyp << endl;
					cout << "-----------------------------------" << endl;
					f.select(ti.base);
					attack(hwnd);

					clock_t watch_dog_start = clock();
					while (f.getHyp(ti) < 0.2 && f.getSelect() != 0) {
						clock_t watch_dog_end = clock();
						if ((((float)watch_dog_end - watch_dog_start) / CLOCKS_PER_SEC) > 5.0) {
							cancel_target(hwnd);
							break;
						}
					}

					/*while (f.getHyp(ti) >= 0.2) {
						if (f.getSelect() != 0) {
							aoe_attack(hwnd);
						}
						else {
							break;
						}
					}*/
				}
				rotate_map(hwnd);
			}
		}
	}

	return 0;
}
