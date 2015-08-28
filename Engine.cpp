#include "Engine.h"

#include <iostream>

[junk_enable /]
[enc_string_enable /]

CEngine::CEngine() {
	[swap_lines]
	_modClient = { 0, 0 };
	_modEngine = { 0, 0 };
	_init = false;
	[/swap_lines]
}

void CEngine::start() {
	while (!mem.Attach("csgo.exe")) {
		Sleep(100);
	}
	Sleep(1000);
	_ofs.getOffsets(&mem);
	_init = true;
}

PModule* CEngine::getClientModule() {
	if (_modClient.dwBase == 0 && _modClient.dwSize == 0) {
		_modClient = mem.GetModule("client.dll");
	}

	return &_modClient;
}

PModule* CEngine::getEngineModule() {
	if (_modEngine.dwBase == 0 && _modEngine.dwSize == 0) {
		_modEngine = mem.GetModule("engine.dll");
	}

	return &_modEngine;
}

bool CEngine::initialized() {
	return _init;
}

PMemory* CEngine::Memory() {
	return &mem;
}

COffsets* CEngine::Offsets() {
	return &_ofs;
}

void CEngine::update() {
	Entity players[64];
	while (true) {
		DWORD playerBase = mem.Read<DWORD>(getClientModule()->dwBase + _ofs.dwLocalPlayer);
		int hp = mem.Read<int>(playerBase + _ofs.dwHealth);
		updateEntityData(&me, playerBase);

		int cp = 0;

		for (int i = 1; i < 64; i++) {
			DWORD entBase = mem.Read<DWORD>((getClientModule()->dwBase + _ofs.dwEntityList) + i * 0x10);

			if (entBase == NULL)
				continue;

			updateEntityData(&players[cp], entBase);

			cp++;
		}

		int cf = 0, ce = 0;

		for (int i = 0; i < cp; i++) {
			if (players[i].team == me.team) {
				entFriendlies[cf] = players[i];
				cf++;
			}
			else {
				entEnemies[ce] = players[i];
				ce++;
			}
		}

		iEnemies = ce;
		iFriendlies = cf;

		Sleep(1);
	}
}

void CEngine::updateEntityData(Entity* e, DWORD dwBase) {
	e->dwBase = dwBase;
	e->id = mem.Read<int>(dwBase + _ofs.dwId);
	e->hp = mem.Read<int>(dwBase + _ofs.dwHealth);
	e->team = mem.Read<int>(dwBase + _ofs.dwTeam);

	DWORD hWeapon = mem.Read<DWORD>(dwBase + _ofs.dwActiveWeapon);
	int weaponEntId = hWeapon & 0xFFF;
	DWORD dwWeaponBase = mem.Read<DWORD>(_modClient.dwBase + _ofs.dwEntityList + (weaponEntId - 1) * 0x10);
	e->weapon_id = mem.Read<int>(dwWeaponBase + _ofs.dwWeaponId);
	e->weapon_ammo = mem.Read<int>(dwWeaponBase + _ofs.dwAmmo);
}