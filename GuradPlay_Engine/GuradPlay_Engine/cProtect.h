#pragma once
#include <windows.h>
#include <tlhelp32.h>
class cProtect
{
	public:
		cProtect(void);
		~cProtect(void);
		void _HideModule(HINSTANCE hModule);
		private:
};

