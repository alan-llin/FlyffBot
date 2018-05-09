#include <vector>
#include <Windows.h>

#ifndef SUMMONER_H
#define SUMMONER_H

unsigned long get_module(unsigned long pid, char* module_name, unsigned long *size = 0);
void command_buff(HWND hwnd);
void F2_buff(HWND hwnd);
void F3_buff(HWND hwnd);
void F4_buff(HWND hwnd);
void F5_buff(HWND hwnd);
void F6_buff(HWND hwnd);
void F7_buff(HWND hwnd);
void all_buff(HWND hwnd);
void attack(HWND hwnd);
void rotate_map(HWND hwnd);
void cancel_target(HWND hwnd);
void aoe_attack(HWND hwnd);

class math {
	public:
		static float sqrt(float number);
};

#endif // !SUMMONER_H

