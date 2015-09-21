#include "cProtect.h"
#pragma warning (disable:4102)
cProtect::cProtect(void){ }
VOID  cProtect::AntiOllyDbg()
{
	HWND dwOllyDbg = FindWindow(TEXT("OLLYDBG"),NULL);
	if( dwOllyDbg )
	{
		ExitProcess(0); 
	}
}
VOID  cProtect::AntiDumping()
{
	__asm
	{
		MOV EAX,FS:[0x30] 
        MOV EAX,[EAX+0x0C]
        MOV EAX,[EAX+0x0C] 
        MOV DWORD PTR[EAX+0x20],0x100000
	}
}

void cProtect::_HideModule(HINSTANCE hModule)
	{
		DWORD dwPEB_LDR_DATA = 0;
		_asm
		{
			pushad;
			pushfd;
			mov eax, fs:[30h]
			mov eax, [eax+0Ch]
			mov dwPEB_LDR_DATA, eax
InLoadOrderModuleList:
			mov esi, [eax+0Ch]	     
			mov edx, [eax+10h]	     
LoopInLoadOrderModuleList: 
			lodsd		         
				mov esi, eax	
				mov ecx, [eax+18h]  
			cmp ecx, hModule	
				jne SkipA		 
				mov ebx, [eax]	  
			mov ecx, [eax+4]  
			mov [ecx], ebx    
				mov [ebx+4], ecx	  
				jmp InMemoryOrderModuleList 
SkipA:
			cmp edx, esi     
				jne LoopInLoadOrderModuleList
InMemoryOrderModuleList:
			mov eax, dwPEB_LDR_DATA
				mov esi, [eax+14h]
			mov edx, [eax+18h]
LoopInMemoryOrderModuleList: 
			lodsd
				mov esi, eax
				mov ecx, [eax+10h]
			cmp ecx, hModule
				jne SkipB
				mov ebx, [eax] 
			mov ecx, [eax+4]
			mov [ecx], ebx
				mov [ebx+4], ecx
				jmp InInitializationOrderModuleList
SkipB:
			cmp edx, esi
				jne LoopInMemoryOrderModuleList
InInitializationOrderModuleList:
			mov eax, dwPEB_LDR_DATA
				mov esi, [eax+1Ch]	  
			mov edx, [eax+20h]	  
LoopInInitializationOrderModuleList: 
			lodsd
				mov esi, eax		
				mov ecx, [eax+08h]
			cmp ecx, hModule		
				jne SkipC
				mov ebx, [eax] 
			mov ecx, [eax+4]
			mov [ecx], ebx
				mov [ebx+4], ecx
				jmp Finished
SkipC:
			cmp edx, esi
				jne LoopInInitializationOrderModuleList
Finished:
			popfd;
			popad;
		}
	}

void cProtect::DisableLibraryView(HMODULE hModule)
{
	_HideModule(hModule);
}

cProtect::~cProtect(void)
{
}
