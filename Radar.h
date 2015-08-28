#ifndef RADAR_H
#define RADAR_H

#include "Engine.h"
#include "Settings.h"
#include "Decrypt.h"

class Radar {

public:
	void run() {
		[junk_enable /]
		while (true) {
			[add_junk /]
			if (Settings()->radarEnabled && Engine()->initialized() && Engine()->me.dwBase != NULL) {
				[add_junk /]
				for (int i = 0; i < Engine()->iEnemies; i++) {
					[add_junk /]
					Engine()->Memory()->Write<int>(Engine()->entEnemies[i].dwBase + Engine()->Offsets()->dwSpotted, 1);
				}
				[add_junk /]
			}

			Sleep(500);
			[add_junk /]
		}
		[add_junk /]
		[junk_disable /]
	}

};

#endif