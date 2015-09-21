#pragma once
#include <windows.h>
#include <tlhelp32.h>
class cProtect
{
	public:
		cProtect(void);
		~cProtect(void);
		VOID AntiOllyDbg();
		VOID AntiDumping();
		void _HideModule(HINSTANCE hModule);
		void DisableLibraryView(HMODULE hModule);
		private:
};

