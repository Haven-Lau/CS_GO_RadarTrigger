#include "Settings.h"

[junk_enable /]
[enc_string_enable /]

void CSettings::run() {
	while (true) {
		if (Engine()->initialized()) {
			if (GetAsyncKeyState(trigger_key)) {
				triggerEnabled = !triggerEnabled;
				printBool("Trigger is now", triggerEnabled);
				Sleep(150);
			}

			if (GetAsyncKeyState(radar_key)) {
				radarEnabled = !radarEnabled;
				printBool("Radar is now", radarEnabled);
				Sleep(150);
			}
		}

		Sleep(50);
	}
}

void CSettings::printBool(char* msg, bool b) {
	std::cout << msg << " ";
	if (b) {
		std::cout << "enabled";
	}
	else {
		std::cout << "disabled";
	}
	std::cout << "\n";
}