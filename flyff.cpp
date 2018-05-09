#include "flyff.h"
#include "summoner.h"
#include <Windows.h>
#include <windows.h>

flyff::flyff(void *handle, unsigned long base_addr) {
	_handle = handle;
	_base_addr = base_addr;
	_select_addr = base_addr + 0x494E58;
	_maxInView_addr = base_addr + 0x609770;
	_targetBase_addr = base_addr + 0x604950;
	_char_addr = base_addr + 0x491138;
}

void flyff::select(unsigned long target) {
	unsigned long pointed = 0;
	ReadProcessMemory(_handle, (LPCVOID)(_select_addr),&pointed,sizeof(pointed),0);
	WriteProcessMemory(_handle, (LPVOID)(pointed+0x20), &target, sizeof(target), 0);
}
unsigned long flyff::getSelect(){
	unsigned long pointed = 0;
	ReadProcessMemory(_handle, (LPCVOID)(_select_addr), &pointed, sizeof(pointed), 0);
	ReadProcessMemory(_handle, (LPVOID)(pointed + 0x20), &pointed, sizeof(pointed), 0);
	return pointed;
}
unsigned long flyff::getMe() {
	unsigned long value = 0;
	ReadProcessMemory(_handle, (LPCVOID)(_char_addr), &value, sizeof(value), 0);
	return value;
}
float flyff::getHyp(targetInfo ti) {
	float x, z;
	ReadProcessMemory(_handle, (LPCVOID)(getMe()+0x164), &x, sizeof(x), 0);
	ReadProcessMemory(_handle, (LPCVOID)(getMe()+0x16C), &z, sizeof(z), 0);
	return math::sqrt((x - ti.x)*(x - ti.x)+ (z - ti.z)*(z - ti.z));
}

unsigned long flyff::getHp() {
	unsigned long target = 0;
	unsigned long hp = 0;
	ReadProcessMemory(_handle, (LPCVOID)(_targetBase_addr), &target, sizeof(target), 0);
	ReadProcessMemory(_handle, (LPCVOID)(target + 0x718), &hp, sizeof(hp), 0);
	return hp;
}

flyff::targetInfo flyff::getClosestTargetInView() {
	unsigned long maxInView = 0;
	targetInfo closest_ti = targetInfo();
	ReadProcessMemory(_handle, (LPCVOID)(_maxInView_addr), &maxInView, sizeof(maxInView), 0);
	for (unsigned long i = 0; i < maxInView; i++) {
		unsigned long target = 0;
		unsigned long type = 0;
		unsigned long pet_type = 0;
		unsigned long lvl = 0;
		unsigned long hp = 0;

		ReadProcessMemory(_handle, (LPCVOID)(i * 4 + _targetBase_addr), &target, sizeof(target), 0);
		ReadProcessMemory(_handle, (LPCVOID)(target+4), &type, sizeof(type), 0);
		ReadProcessMemory(_handle, (LPCVOID)(target+0x6F4), &lvl, sizeof(lvl), 0);
		ReadProcessMemory(_handle, (LPCVOID)(target+0x718), &hp, sizeof(hp), 0);
		ReadProcessMemory(_handle, (LPCVOID)(target + 0x728), &pet_type, sizeof(pet_type), 0);

		if (target != getMe() && type == 18 && lvl > 0 && lvl < 10000 && hp > 1 && pet_type != 19) {
			targetInfo ti;
			ReadProcessMemory(_handle, (LPCVOID)(target + 0x164), &ti.x, sizeof(ti.x), 0);
			ReadProcessMemory(_handle, (LPCVOID)(target + 0x168), &ti.y, sizeof(ti.y), 0);
			ReadProcessMemory(_handle, (LPCVOID)(target + 0x16C), &ti.z, sizeof(ti.z), 0);
			ti.hyp = getHyp(ti);

			if (ti.hyp > closest_ti.hyp) {
				ti.base = target;
				ti.lvl = lvl;
				ti.hp = hp;
				ReadProcessMemory(_handle, (LPCVOID)(target + 0x1BB0), &ti.name, 255, 0);
				closest_ti = ti;
			}

		}
	}
	return closest_ti;

}
