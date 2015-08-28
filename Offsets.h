#ifndef OFFSETS_H
#define OFFSETS_H

#include "PMemory.h"
#include "Decrypt.h"

#include <string>
#include <sstream>

class COffsets {
public:
	DWORD dwLocalPlayer;
	DWORD dwEntityList;
	DWORD dwAttack;
	
	DWORD dwActiveWeapon = 0x12C0;
	DWORD dwWeaponId = 0x168C;
	DWORD dwInCross = 0x2410;
	DWORD dwSpotted = 0x935;
	DWORD dwId = 0x64;
	DWORD dwHealth = 0xFC;
	DWORD dwTeam = 0xF0;
	DWORD dwAmmo = 0x15C0;

	std::string toHex(DWORD offset);

	void getOffsets(PMemory* m);

private:
	PMemory* mem;
	PModule modClient;

	void updateLocalPlayer();
	void updateEntityList();
	void updateAttack();

};

#endif