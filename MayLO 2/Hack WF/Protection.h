#include <Windows.h>
#include <TlHelp32.h>

void AntiHeaders(HINSTANCE hModule)
{
	DWORD dwPEB_LDR_DATA = 0;
	_asm
	{
		pushad;
		pushfd;
		mov eax, fs:[30h]
			mov eax, [eax + 0Ch]
			mov dwPEB_LDR_DATA, eax

		InLoadOrderModuleList :
		mov esi, [eax + 0Ch]
			mov edx, [eax + 10h]

		LoopInLoadOrderModuleList :
								  lodsd
								  mov esi, eax
								  mov ecx, [eax + 18h]
								  cmp ecx, hModule
								  jne SkipA
								  mov ebx, [eax]
								  mov ecx, [eax + 4]
								  mov[ecx], ebx
								  mov[ebx + 4], ecx
								  jmp InMemoryOrderModuleList
							  SkipA :
		cmp edx, esi
			jne LoopInLoadOrderModuleList

		InMemoryOrderModuleList :
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax + 14h]
			mov edx, [eax + 18h]

		LoopInMemoryOrderModuleList :
									lodsd
									mov esi, eax
									mov ecx, [eax + 10h]
									cmp ecx, hModule
									jne SkipB
									mov ebx, [eax]
									mov ecx, [eax + 4]
									mov[ecx], ebx
									mov[ebx + 4], ecx
									jmp InInitializationOrderModuleList
								SkipB :
		cmp edx, esi
			jne LoopInMemoryOrderModuleList

		InInitializationOrderModuleList :
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax + 1Ch]
			mov edx, [eax + 20h]

		LoopInInitializationOrderModuleList :
											lodsd
											mov esi, eax
											mov ecx, [eax + 08h]
											cmp ecx, hModule
											jne SkipC
											mov ebx, [eax]
											mov ecx, [eax + 4]
											mov[ecx], ebx
											mov[ebx + 4], ecx
											jmp Finished
										SkipC :
		cmp edx, esi
			jne LoopInInitializationOrderModuleList

		Finished :
		popfd;
		popad;
	}
}

void AntiDumping()
{
	__asm
	{
		MOV EAX, FS:[0x30]
			MOV EAX, [EAX + 0x0C]
			MOV EAX, [EAX + 0x0C]
			MOV DWORD PTR[EAX + 0x20], 0x100000
	}
}

PVOID AntiRevers(HMODULE dwModule)
{
	PVOID pEntry = NULL;
	PIMAGE_DOS_HEADER pId = (PIMAGE_DOS_HEADER)dwModule;
	PIMAGE_NT_HEADERS pInt = (PIMAGE_NT_HEADERS)(dwModule + pId->e_lfanew);
	pEntry = dwModule + pInt->OptionalHeader.BaseOfCode;
	return pEntry;
}

void HideModule(HINSTANCE hModule)
{
	DWORD dwPEB_LDR_DATA = 0;
	_asm
	{
		pushad;
		pushfd;
		mov eax, fs:[30h]
			mov eax, [eax + 0Ch]
			mov dwPEB_LDR_DATA, eax
		InLoadOrderModuleList :
		mov esi, [eax + 0Ch]
			mov edx, [eax + 10h]
		LoopInLoadOrderModuleList :
								  lodsd
								  mov esi, eax
								  mov ecx, [eax + 18h]
								  cmp ecx, hModule
								  jne SkipA
								  mov ebx, [eax]
								  mov ecx, [eax + 4]
								  mov[ecx], ebx
								  mov[ebx + 4], ecx
								  jmp InMemoryOrderModuleList
							  SkipA :
		cmp edx, esi
			jne LoopInLoadOrderModuleList
		InMemoryOrderModuleList :
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax + 14h]
			mov edx, [eax + 18h]
		LoopInMemoryOrderModuleList :
									lodsd
									mov esi, eax
									mov ecx, [eax + 10h]
									cmp ecx, hModule
									jne SkipB
									mov ebx, [eax]
									mov ecx, [eax + 4]
									mov[ecx], ebx
									mov[ebx + 4], ecx
									jmp InInitializationOrderModuleList
								SkipB :
		cmp edx, esi
			jne LoopInMemoryOrderModuleList
		InInitializationOrderModuleList :
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax + 1Ch]
			mov edx, [eax + 20h]
		LoopInInitializationOrderModuleList :
											lodsd
											mov esi, eax
											mov ecx, [eax + 08h]
											cmp ecx, hModule
											jne SkipC
											mov ebx, [eax]
											mov ecx, [eax + 4]
											mov[ecx], ebx
											mov[ebx + 4], ecx
											jmp Finished
										SkipC :
		cmp edx, esi
			jne LoopInInitializationOrderModuleList
		Finished :
		popfd;
		popad;
	}
}
HWND findwind(const char * str){
	HWND hWnd;
	char buffer[1024];
	hWnd = FindWindowEx(NULL, NULL, NULL, NULL);
	while (hWnd){
		GetWindowText(hWnd, buffer, 1000);
		if (buffer == strstr(buffer, str)) return hWnd;
		hWnd = FindWindowEx(NULL, hWnd, NULL, NULL);
	}
	return NULL;
}
void Protect()
{
	HWND hWnd = findwind("Cheat");
	if (hWnd)
	{
		PostMessage(hWnd, WM_QUIT, 0, 0);
		MessageBoxA(NULL, "Обнаружен Cheat Engine!", "Ай-я-яй", MB_OK);
	}
	HWND hWnd1 = findwind("PE");
	if (hWnd1)
	{
		PostMessage(hWnd1, WM_QUIT, 0, 0);
		MessageBoxA(NULL, "Обнаружен дампер!", "Ай-я-яй", MB_OK);
	}
	HWND hWnd2 = findwind("Olly");
	if (hWnd2)
	{
		PostMessage(hWnd2, WM_QUIT, 0, 0);
		MessageBoxA(NULL, "Обнаружена OLLYDBG!", "Ай-я-яй", MB_OK);
	}
	HWND hWnd3 = findwind("Dump");
	if (hWnd3)
	{
		PostMessage(hWnd3, WM_QUIT, 0, 0);
		MessageBoxA(NULL, "Обнаружен дампер!", "Ай-я-яй", MB_OK);
	}
	HWND hWnd4 = findwind("Дамп");
	if (hWnd4)
	{
		PostMessage(hWnd4, WM_QUIT, 0, 0);
		MessageBoxA(NULL, "Обнаружен дампер!", "Ай-я-яй", MB_OK);
	}
	HWND hWnd5 = findwind("dump");
	if (hWnd5)
	{
		PostMessage(hWnd5, WM_QUIT, 0, 0);
		MessageBoxA(NULL, "Обнаружен дампер!", "Ай-я-яй", MB_OK);
	}
	HWND hWnd6 = findwind("дамп");
	if (hWnd6)
	{
		PostMessage(hWnd6, WM_QUIT, 0, 0);
		MessageBoxA(NULL, "Обнаружен дампер!", "Ай-я-яй", MB_OK);
	}
	HWND hWnd7 = findwind("Engine");
	if (hWnd7)
	{
		PostMessage(hWnd7, WM_QUIT, 0, 0);
		MessageBoxA(NULL, "Обнаружен Cheat Engine!", "Ай-я-яй", MB_OK);
	}
	HWND hWnd8 = findwind("Mega");
	if (hWnd8)
	{
		PostMessage(hWnd8, WM_QUIT, 0, 0);
		MessageBoxA(NULL, "Обнаружен дампер!", "Ай-я-яй", MB_OK);
	}
	HWND hWnd9 = findwind("CodeCrack");
	if (hWnd9)
	{
		PostMessage(hWnd9, WM_QUIT, 0, 0);
		MessageBoxA(NULL, "Обнаружен дампер!", "Ай-я-яй", MB_OK);
	}
}
void AntiDebug()
{
	typedef unsigned long(__stdcall *pfnNtQueryInformationProcess)(IN  HANDLE, IN  unsigned int, OUT PVOID, IN ULONG, OUT PULONG);
	const int ProcessDbgPort = 7;
	pfnNtQueryInformationProcess NtQueryInfoProcess = NULL;
	unsigned long Ret;
	unsigned long IsRemotePresent = 0;
	HMODULE hNtDll = LoadLibrary(TEXT("ntdll.dll"));
	if (hNtDll == NULL){}
	NtQueryInfoProcess = (pfnNtQueryInformationProcess)
		GetProcAddress(hNtDll, "NtQueryInformationProcess");
	if (NtQueryInfoProcess == NULL){}
	Ret = NtQueryInfoProcess(GetCurrentProcess(), ProcessDbgPort, &IsRemotePresent, sizeof(unsigned long), NULL);
	if (Ret == 0x00000000 && IsRemotePresent != 0)
	{
		ExitProcess(0);
	}
}

HRESULT APIENTRY protect()
{
	AntiDumping();
	return 0;
}