#include "Offsets.h"

#include <iostream>

[junk_enable /]
[enc_string_enable /]

std::string COffsets::toHex(DWORD offset) {
    std::stringstream ss;
    ss << std::hex << offset;
    std::string x = ss.str();
    for (auto &c : x) c = toupper(c);

    return x;
}

void COffsets::getOffsets(PMemory* m) {
    mem = m;

    modClient = mem->GetModule("client.dll");

    updateLocalPlayer();
    updateEntityList();
    updateAttack();
}

void COffsets::updateLocalPlayer() {
    DWORD lpStart = mem->FindPatternArr(modClient.dwBase, modClient.dwSize, "xxx????xx????xxxxx?", 19, 0x8D, 0x34, 0x85, 0x0, 0x0, 0x0, 0x0, 0x89, 0x15, 0x0, 0x0, 0x0, 0x0, 0x8B, 0x41, 0x8, 0x8B, 0x48, 0x0);
    DWORD lpP1 = mem->Read<DWORD>(lpStart + 3);
    BYTE lpP2 = mem->Read<BYTE>(lpStart + 18);
    dwLocalPlayer = (lpP1 + lpP2) - modClient.dwBase;
}

void COffsets::updateEntityList() {
    DWORD elStart = mem->FindPatternArr(modClient.dwBase, modClient.dwSize, "x????xx?xxx", 11, 0x5, 0x0, 0x0, 0x0, 0x0, 0xC1, 0xE9, 0x0, 0x39, 0x48, 0x4);
    DWORD elP1 = mem->Read<DWORD>(elStart + 1);
    BYTE elP2 = mem->Read<BYTE>(elStart + 7);
    dwEntityList = (elP1 + elP2) - modClient.dwBase;
}

void COffsets::updateAttack() {
    DWORD aStart = mem->FindPatternArr(modClient.dwBase, modClient.dwSize, "xx????xx????xxxxxxxxxxx", 23, 0x89, 0x15, 0x0, 0x0, 0x0, 0x0, 0x8B, 0x15, 0x0, 0x0, 0x0, 0x0, 0xF6, 0xC2, 0x3, 0x74, 0x3, 0x83, 0xCE, 0x4, 0xA8, 0x4, 0xBF);
    DWORD aOff = mem->Read<DWORD>(aStart + 2);
    dwAttack = aOff - modClient.dwBase;
}
