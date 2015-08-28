#ifndef ENGINE_H
#define ENGINE_H

#include <thread>

#include "PMemory.h"
#include "Offsets.h"

#include "Decrypt.h"

struct Entity {
	[swap_lines]
	DWORD dwBase;
	int id;
	int hp;
	int team;
	int weapon_id;
	int weapon_ammo;
	[/swap_lines]
};

class CEngine {
public:
	[junk_enable 2 5 /]
	[junk_enable_declares /]
	[swap_lines]
	CEngine();

	void start();

	void update();

	bool initialized();

	PMemory* Memory();
	COffsets* Offsets();

	PModule* getClientModule();
	PModule* getEngineModule();

	int iFriendlies;
	int iEnemies;
	Entity entEnemies[32];
	Entity entFriendlies[32];
	Entity me;
	[/swap_lines]
	[junk_disable /]

private:
	[junk_enable 2 5 /]
	[junk_enable_declares /]
	PMemory mem;
	PModule _modClient, _modEngine;
	COffsets _ofs;
	bool _init;

	void updateEntityData(Entity* e, DWORD dwBase);
	[junk_disable /]
};

inline CEngine* Engine() {
	static CEngine instance;
	[add_junk /]
	return &instance;
}

#endif