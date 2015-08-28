#ifndef TRIGGERBOT_H
#define TRIGGERBOT_H

#include "Engine.h"
#include "Settings.h"
#include "Decrypt.h"

class Triggerbot {

public: 
	void run() {
		[junk_enable /]
		while (true) {
			[add_junk /]
			if (Settings()->triggerEnabled) {
				[add_junk /]
				Entity* inX = inCrosshair();

				if (inX != nullptr && Engine()->me.weapon_ammo > 0 && inX->hp > 0 && (Settings()->trigger_holdkey == 0 || GetAsyncKeyState(Settings()->trigger_holdkey))) {
					Engine()->Memory()->Write<int>(Engine()->getClientModule()->dwBase + Engine()->Offsets()->dwAttack, 5);
					Sleep(10);
					if (!GetAsyncKeyState(VK_LBUTTON)) {
						Engine()->Memory()->Write<int>(Engine()->getClientModule()->dwBase + Engine()->Offsets()->dwAttack, 4);
					}
				}
				[add_junk /]
			}

			Sleep(1);
		}
		[add_junk /]
		[junk_disable /]
	}

private:
	Entity* inCrosshair() {
		[junk_enable /]
		[add_junk /]
		int idInX = Engine()->Memory()->Read<int>(Engine()->me.dwBase + Engine()->Offsets()->dwInCross);

		if (idInX != 0) {
			[add_junk /]
			for (int i = 0; i < Engine()->iEnemies; i++) {
				if (Engine()->entEnemies[i].id == idInX) {
					return &Engine()->entEnemies[i];
				}
			}
			[add_junk /]
		}

		[junk_disable /]
		return nullptr;
	}

};

#endif