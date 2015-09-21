#ifndef _asma_h
#define _asma_h

//Модули//
DWORD PB = (DWORD)GetModuleHandleA("PBlackout.exe");
DWORD Frame = (DWORD)GetModuleHandleA("i3frameworkdx.dll");
//HMODULE PBlackout_i3exec=GetModuleHandleA("PBlackout.i3Exec");//Модуль   
//Модули//


//адреса в модуле
//DWORD Addres_GetMoveSpe =  (DWORD)PBlackout_i3exec  +0x184EAC;//ДН/скорострел/антиотдача
void _fastcall Click()
{
	MEMwrite((void *)((DWORD)GetModuleHandleA("i3inputDx.dll") + 0x22B0),(void *)"\x8B\x41\x01",3);
}
void _fastcall UNClick()
{
	MEMwrite((void *)((DWORD)GetModuleHandleA("i3inputDx.dll") + 0x22B0),(void *)"\x8B\x41\x24",3);
}

//---------------------------------------------Получаем адресса---

DWORD ADDRES_Antioda_1 = 0x4EB1FA;//антиотдача
//DWORD Addres_Skorostrel     =Addres_GetMoveSpe +0x1F0;//скорострел 
//DWORD ADDRES_Knife          =Addres_GetMoveSpe +0x720;//дн
DWORD ADDRES_Antioda_2 = 0x4EB09A;//антиотдача
//DWORD ADDRES_Max_Bullet     =ADDRES_anlim      +0x2D4;//анлимпатроны
DWORD ADDRES_No_Fall_Damage = 0x657F3F;               // Антиурон при падении
DWORD Addres_Speed_Reload = 0x4E6906;      

//-----------------------------------------------Смещение-------------

DWORD RETURN_Antioda_1      =ADDRES_Antioda_1      +0x5;//антиотдача
//DWORD RETURN_Damage         =ADDRES_Damage         +0x5;
//DWORD RETURN_Skorostrel     =Addres_Skorostrel     +0x5;//скорострел
//DWORD RETURN_Knife          =ADDRES_Knife          +0x5;//ДН
DWORD RETURN_Antioda_2      =ADDRES_Antioda_2      +0x5;//антиотдача
DWORD RETURN_Speed_Reload   =Addres_Speed_Reload   +0x6;//перезарядка
//DWORD RETURN_Max_Bullet     =ADDRES_Max_Bullet     +0x6;// анлим патроны
DWORD RETURN_No_Fall_Damage = ADDRES_No_Fall_Damage +0x5;// Антиурон при падении


//=============AutoShot===========
DWORD adr_autoshot_1 =0x01087A;// i3Framework::GetViewer(void)  +17A  (FF 15 64  5C 8E 00)
DWORD adr_autoshot_2 = adr_autoshot_1 + 0x8;//5D0257//0x01087A
DWORD ret_autoshot = adr_autoshot_1 + 0x26;
DWORD ret_autoshot_2 = adr_autoshot_2 + 0xA;


//float skorostrel=0.01;
float rel=1000;

//float logm=300;
float buffer;
//float hover=0.1;
//float dam;
//float miganie;
//float patron=1;        //Анлим патроны
float NFD;             //АНти дамаг падения
 





/*//Дамаг
 __declspec( naked ) void Damage()
{
 
 _asm
 {
  fld dword ptr [dam]
  mov esp,ebp
  jmp dword ptr [RETURN_Damage]
 }
}

__declspec( naked ) void DamageUnhook()
{
 _asm
 {
  fld dword ptr [ebp-14]
  mov esp,ebp
  jmp dword ptr [RETURN_Damage]
 }
}
//Дамаг


/*
//Ховер
__declspec(naked)void hover_on()
{
_asm
{ 
	mov    eax,dword ptr[hover]
   mov    [ebx+11Ch], eax
   jmp    dword ptr [RETURN_hover]
}
}
__declspec(naked)void hover_off()
{
_asm
{ 
	mov    eax, dword ptr[esi+14h]
   mov    [ebx+11Ch], eax
   jmp    dword ptr [RETURN_hover]
}
}
//Ховер                   */






//Скорострел
/*__declspec(naked)void Skorostrel_on()
{
_asm
{
fld dword ptr[skorostrel]
mov esp,ebp
jmp dword ptr[RETURN_Skorostrel]
}
}

__declspec(naked)void Skorostrel_off()
{
_asm
{
fld dword ptr[ebp-04]
mov esp,ebp
jmp dword ptr[RETURN_Skorostrel]
}
}
*/
//Перезарядка
__declspec( naked ) void sreload_on()
{
 _asm
 {
  fstp dword ptr [ebp-0x0C]
  movss [buffer],xmm0
  movss xmm0,[rel]
  movss [ebp-0x0C],xmm0
  movss xmm0,[buffer]
  mov ecx,[ebp-0x80]
  jmp [RETURN_Speed_Reload]
 }
}
__declspec( naked ) void sreload_off()
{
 _asm
 {
  fstp dword ptr [ebp-0x0C]
  mov ecx,[ebp-0x80]
  jmp [RETURN_Speed_Reload]
 }
}

/*ДН
__declspec(naked)void knife()
{
_asm
{
fld dword ptr[logm]
mov esp,ebp
jmp dword ptr[RETURN_Knife]
}
}
__declspec(naked)void knifeUnhook()
{
_asm
{
fld dword ptr[ebp-04]
mov esp,ebp
jmp dword ptr[RETURN_Knife]
}
}*/



//------------анти отдача-----------
float ant=0;
__declspec( naked ) void Antioda_1_on()
{
 _asm
 {
  fld  [ant]
  mov esp,ebp
  jmp dword ptr [RETURN_Antioda_1]
 }
}
__declspec( naked ) void Antioda_1_off()
{
 _asm
 {
  fld     [ebp-8]
  mov esp,ebp
  jmp dword ptr [RETURN_Antioda_1]
 }
}
__declspec( naked ) void Antioda_2_on()
{
 _asm
 {
  fld [ant]
  mov esp,ebp
  jmp dword ptr [RETURN_Antioda_2]
 }
}
__declspec( naked ) void Antioda_2_off()
{
 _asm
 {
  fld [ebp-8]
  mov esp,ebp
  jmp dword ptr [RETURN_Antioda_2]
 }
}
/*//-----------Анлим патроны----------
__declspec( naked ) void Max_Bullet_on()
{
 _asm
 {
  mov eax,[patron]
  pop esi
  mov esp,ebp
  jmp dword ptr [RETURN_Max_Bullet]
 }
}
__declspec( naked ) void Max_Bullet_off()
{
 _asm
 {
  mov     eax, [ebp-4]
  pop esi
  mov esp,ebp
  jmp dword ptr [RETURN_Max_Bullet]
 }
}*/

//----------Дамаг от падения----------------

__declspec(naked)void No_Fall_Damage_on()
{
_asm
{
mov     eax, [NFD]
mov     esp, ebp
jmp dword ptr[RETURN_No_Fall_Damage]
}
}

__declspec(naked)void No_Fall_Damage_off()
{
_asm
{
mov     eax, [ebp-4]
mov     esp, ebp
jmp dword ptr[RETURN_No_Fall_Damage]
}
}
//autoshot
__declspec(naked)void autoshot_1()
{ 
_asm
{
mov     [ecx+358], al
call    [UNClick]
jmp [ret_autoshot]
}
}
__declspec(naked)void autoshot_2()
{ 
_asm
{
mov     ecx, [ebp-32]
mov     byte ptr [ecx+356], 255
call    [Click]
jmp  [ret_autoshot_2]
}
}

__declspec(naked)void autoshot_1_off()
{ 
_asm
{
mov     [ecx+358], al
jmp [ret_autoshot]
}
}
__declspec(naked)void autoshot_2_off()
{ 
_asm
{
mov     ecx, [ebp-32]
mov     byte ptr [ecx+356], 255
jmp  [ret_autoshot_2]
}
}
#endif