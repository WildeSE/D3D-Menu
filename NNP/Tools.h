
//-----------------------------------------------------------------------------
// Exam: FPS() or __FPS__
// Desc: Кадров в секунду
// Сonc: Menu
//-----------------------------------------------------------------------------

char* FPS(void)
{
	static int FPScounter = 0;
	static float FPSfLastTickCount = 0.0f;
	static float FPSfCurrentTickCount;
	static char cfps[6] = "";

	FPSfCurrentTickCount = clock() * 0.001f;
	FPScounter++;
	if((FPSfCurrentTickCount - FPSfLastTickCount) > 1.0f)
	{
			FPSfLastTickCount = FPSfCurrentTickCount;
			sprintf(cfps," %d",FPScounter);
			FPScounter = 0;
			return cfps;
	}
}

//-----------------------------------------------------------------------------
// Exam: Time() or __Time__
// Desc: Время ENG .
// Сonc: Menu
//-----------------------------------------------------------------------------

char* Time(void)
{
	static char ctime[20] = "" ;
	struct tm * current_tm;
	time_t current_time;
	time (&current_time);
	current_tm = localtime (&current_time);
	if(current_tm->tm_hour>12)
		sprintf( ctime, "%d:%02d:%02d PM", current_tm->tm_hour - 12, current_tm->tm_min, current_tm->tm_sec );
	else
		sprintf( ctime, "%d:%02d:%02d AM", current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec );
	return ctime;
}

//-----------------------------------------------------------------------------
// Exam: Date() or __Date__
// Desc: Дата ENG .
// Сonc: Menu
//-----------------------------------------------------------------------------

char* Date(void)
{
	struct tm * current_tm;
	time_t current_time;time (&current_time);
	current_tm = localtime (&current_time);
	char *month []={"Jan.","Feb.","Mar.","Apr.","May","June","July","Aug.","Sept.","Oct.","Nov.","Dec."};
	char *logbuf = new char[ 256 ];

	sprintf( logbuf, "%s%02d.20%d",month[current_tm->tm_mon],current_tm->tm_mday,current_tm->tm_year-100);
	return logbuf;
}

//-----------------------------------------------------------------------------
// Комплектующие Load и Save
//-----------------------------------------------------------------------------

FILE *LOG;
char dllpath[255];
char logfile[255];

char* GetFile(char *file)
{
	static char path[320];
	for(int i= 0;i<strlen(path);i++)
	path[i]=0;
	strcpy(path, dllpath);
	strcat(path, file);
	return path;
}



//-----------------------------------------------------------------------------
// Exam: Переменная=Load(Sett,"Название",Переменная,Patch);
// Desc: Загрузка предварительно сохранённых опций .
// Сonc: Options/Tools
//-----------------------------------------------------------------------------

char *Sett = "TSMI WarFace, Пользовательские настройки";
char *Patch = GetFile("C:\TSMI WarFace.dat");

int Load(char* szSection, char* szKey, int iDefaultValue,LPCSTR file)
{
	int iResult = GetPrivateProfileInt(szSection, szKey, iDefaultValue, file);
	return iResult;
}

//-----------------------------------------------------------------------------
// Exam: Save(Sett,"Функция",Переменная,Patch);
// Desc: Сохранение пользовательских опций .
// Сonc: Options/Tools
//-----------------------------------------------------------------------------

void Save(char* szSection, char* szKey, int iValue,LPCSTR file)
{
	char szValue[255];
	sprintf(szValue, "%d", iValue);
	WritePrivateProfileString(szSection, szKey, szValue, file); 
}

//-----------------------------------------------------------------------------
// Exam: OpenURL("http://multiplays.org/");
// Desc: Переход на сайт.
// Сonc: Options/Tools
//-----------------------------------------------------------------------------

void  OpenURL(LPCSTR URL)
{
	ShellExecute(NULL,"open",URL,NULL,NULL,SW_SHOWNORMAL);
	return;
}

//-----------------------------------------------------------------------------
// Exam: TimeWaiting(60);
// Desc: "Подождите пару сек..."
// Сonc: Options/Tools
//-----------------------------------------------------------------------------

void  TimeWaiting(int seconds)
{
	clock_t endwait;
	endwait = clock () + seconds * CLOCKS_PER_SEC ;
	while((clock() < endwait)){	}
	return;
}

//-----------------------------------------------------------------------------
// Exam: Message("Mulriplays.org","Желаемый текст");
// Desc: MessageBox 
// Сonc: Options/Tools
//-----------------------------------------------------------------------------

#define MB(text,head) MessageBox(NULL, text, head, MB_OK);

//-----------------------------------------------------------------------------
// Exam: Dev((DWORD)hD3D9DLL,0x128000);
// Desc: Dev 
// Сonc: Options/Tools
//-----------------------------------------------------------------------------

DWORD* Dev(DWORD Base,DWORD Len)
{
	unsigned long i = 0, n = 0;

	for( i = 0; i < Len; i++ )
	{
        if(*(BYTE *)(Base+i+0x00)==0xC7)n++;
	    if(*(BYTE *)(Base+i+0x01)==0x06)n++;
	    if(*(BYTE *)(Base+i+0x06)==0x89)n++;
	    if(*(BYTE *)(Base+i+0x07)==0x86)n++;	
        if(*(BYTE *)(Base+i+0x0C)==0x89)n++;
	    if(*(BYTE *)(Base+i+0x0D)==0x86)n++;

	    if(n == 6) return (DWORD_PTR *)
			(Base + i + 2);n = 0;
	}
	return(0);
}

//-----------------------------------------------------------------------------
// Exam: DetourCreate((PBYTE)VTable[16], (PBYTE)myReset,     12);
// Desc: DetourCreate 
// Сonc: Hack/Tools
//-----------------------------------------------------------------------------

void * DetourCreate(BYTE *src, const BYTE *dst, const int len)
{
	BYTE *jmp;
	DWORD dwback;
	DWORD jumpto, newjump;

	VirtualProtect(src,len,PAGE_READWRITE,&dwback);

	 if(src[0] == 0xE9)
	 {
		jmp = (BYTE*)malloc(10);
		jumpto = (*(DWORD*)(src+1))+((DWORD)src)+5;
		newjump = (jumpto-(DWORD)(jmp+5));
		jmp[0] = 0xE9;
		*(DWORD*)(jmp+1) = newjump;
		jmp += 5;
		jmp[0] = 0xE9;
		*(DWORD*)(jmp+1) = (DWORD)(src-jmp);
	 }
	 else
	 {
		jmp = (BYTE*)malloc(5+len);
		memcpy(jmp,src,len);
		jmp += len;
		jmp[0] = 0xE9;
		*(DWORD*)(jmp+1) = (DWORD)(src+len-jmp)-5;
	 }
	 src[0] = 0xE9;
	 *(DWORD*)(src+1) = (DWORD)(dst - src) - 5;

	 for(int i = 5; i < len; i++)
	  src[i] = 0x90;
	 VirtualProtect(src, len, dwback, &dwback);
	 return (jmp - len);
}

//-----------------------------------------------------------------------------
// Exam: StartRoutine((PBYTE)VTable[16], (PBYTE)myReset,     12);
// Desc: StartRoutine 
// Сonc: Hack/Tools
//-----------------------------------------------------------------------------

#define StartRoutine(Function) CreateThread(0,0,(LPTHREAD_START_ROUTINE)Function,0,0,0);

//-----------------------------------------------------------------------------
// Exam: StartLogModule(hDll);
// Desc: StartLogModule 
// Сonc: Hack/Tools
//-----------------------------------------------------------------------------

char dlldir[320];

void  StartLogModule(HMODULE hDll)
{
	DisableThreadLibraryCalls(hDll);
	GetModuleFileName(hDll, dlldir, 512);
	for(int i = strlen(dlldir); i > 0; i--)
	{
		if(dlldir[i] == '\\')
		{
			dlldir[i+1] = 0;
			break; 
		} 

	}
}
//-----------------------------------------------------------------------------
// Exam: 
// Desc: 
// Сonc: Hack
//-----------------------------------------------------------------------------

BOOL  bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for(;*szMask;++szMask,++pData,++bMask)
		if(*szMask=='x' && *pData!=*bMask) 
			return false;
	return (*szMask) == NULL;
}

DWORD  FindPattern(DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * szMask)
{
	for(DWORD i=0; i < dwLen; i++)
		if( bCompare((BYTE*)(dwAddress+i),bMask,szMask))
			return (DWORD)(dwAddress+i);

	return 0;
}

//-----------------------------------------------------------------------------
// Exam: PlaySoundMem((LPCSTR)MOVE);
// Desc: Звуки
// Сonc: Sound/Menu
//-----------------------------------------------------------------------------

void PlaySoundFile(LPCSTR sound)
{
	sndPlaySound(sound, SND_ASYNC);
}

void PlaySoundMem(LPCSTR sound)
{
	sndPlaySound(sound, SND_ASYNC|SND_MEMORY);
}

void MEMwrite(void *adr, void *ptr, int size)
{
	DWORD OldProtection;
	VirtualProtect(adr, size, PAGE_EXECUTE_READWRITE, &OldProtection);
	memcpy(adr, ptr, size);
	VirtualProtect(adr, size, OldProtection, &OldProtection);
}