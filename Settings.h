#ifndef SETTINGS_H
#define SETTINGS_H

#include "Engine.h"

#include <iostream>
#include "Decrypt.h"

class CSettings {

public:
    [junk_enable 2 5 /]
    [junk_enable_declares /]
    [swap_lines]
	int trigger_key = VK_F8;
	int trigger_holdkey;
	int radar_key = VK_F9;

	bool triggerEnabled = false;
	bool radarEnabled = false;

	void run();
    [/swap_lines]

private:
	void printBool(char* msg, bool b);
    [junk_disable /]

};

inline CSettings* Settings() {
	static CSettings instance;
    [add_junk /]
	return &instance;
}

#endif