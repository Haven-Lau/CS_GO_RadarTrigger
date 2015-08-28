#include <iostream>

#include "Engine.h"
#include "Settings.h"
#include "Radar.h"
#include "Triggerbot.h"

[junk_enable /]
[enc_string_enable /]

int whichKeyIsPressed() {
	while (true) {
		for (int i = 1; i < 255; i++) {
			if (GetAsyncKeyState(i) & 0x8000) {
				Sleep(250);
				return i;
			}
		}
		Sleep(10);
	}
}

int main() {
	std::cout << "Radar and Trigger\n\n";
	
	Engine()->start();
	std::thread engineThread(&CEngine::update, Engine());

	std::cout << "Found\n\n";
	std::cout << "Offsets\n";
	std::cout << "Local player: 0x" << Engine()->Offsets()->toHex(Engine()->Offsets()->dwLocalPlayer) << "\n";
	std::cout << "Entity list: 0x" << Engine()->Offsets()->toHex(Engine()->Offsets()->dwEntityList) << "\n";
	std::cout << "Attack: 0x" << Engine()->Offsets()->toHex(Engine()->Offsets()->dwAttack) << "\n\n";

	std::cout << "Hotkeys:\n";
	std::cout << "Triggerkey: ";
	Settings()->trigger_key = whichKeyIsPressed();
	std::cout << Settings()->trigger_key << "\n";
	std::cout << "Trigger hold key (press ENTER for no hold key): ";
	Settings()->trigger_holdkey = whichKeyIsPressed();
	if (Settings()->trigger_holdkey == VK_RETURN) {
		Settings()->trigger_holdkey = 0;
	}
	std::cout << Settings()->trigger_holdkey << "\n";
	std::cout << "Radar key: ";
	Settings()->radar_key = whichKeyIsPressed();
	std::cout << Settings()->radar_key << "\n\n";

	std::cout << "The hack is now active!\n\n";

	std::thread settingsThread(&CSettings::run, Settings());
	std::thread radarThread(&Radar::run, Radar());
	std::thread triggerThread(&Triggerbot::run, Triggerbot());

	while (!GetAsyncKeyState(VK_END)) {
		Sleep(100);
	}

	exit(0);

	return 0;
}
