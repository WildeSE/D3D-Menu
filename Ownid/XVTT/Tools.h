
#define MB(text,head) MessageBox(NULL, text, head, MB_OK);


void * DetourCreate(BYTE *src, const BYTE *dst, const int len)
{
	BYTE *jmp;
	DWORD dwback;
	DWORD jumpto, newjump;

	VirtualProtect(src, len, PAGE_READWRITE, &dwback);

	if (src[0] == 0xE9)
	{
		jmp = (BYTE*)malloc(10);
		jumpto = (*(DWORD*)(src + 1)) + ((DWORD)src) + 5;
		newjump = (jumpto - (DWORD)(jmp + 5));
		jmp[0] = 0xE9;
		*(DWORD*)(jmp + 1) = newjump;
		jmp += 5;
		jmp[0] = 0xE9;
		*(DWORD*)(jmp + 1) = (DWORD)(src - jmp);
	}
	else
	{
		jmp = (BYTE*)malloc(5 + len);
		memcpy(jmp, src, len);
		jmp += len;
		jmp[0] = 0xE9;
		*(DWORD*)(jmp + 1) = (DWORD)(src + len - jmp) - 5;
	}
	src[0] = 0xE9;
	*(DWORD*)(src + 1) = (DWORD)(dst - src) - 5;

	for (int i = 5; i < len; i++)
		src[i] = 0x90;
	VirtualProtect(src, len, dwback, &dwback);
	return (jmp - len);
}


#define StartRoutine(Function) CreateThread(0,0,(LPTHREAD_START_ROUTINE)Function,0,0,0);



BOOL  bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
	if (*szMask == 'x' && *pData != *bMask)
		return false;
	return (*szMask) == NULL;
}

DWORD  FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask)
{
	for (DWORD i = 0; i < dwLen; i++)
	if (bCompare((BYTE*)(dwAddress + i), bMask, szMask))
		return (DWORD)(dwAddress + i);

	return 0;
}


//-----------------------------------------------------------------------------



