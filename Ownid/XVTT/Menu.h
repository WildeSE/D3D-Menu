
int S;
int Ar, Ag, Ab;
bool SA;
D3DCOLOR TColOff = DARK18; //Цвет текста    [Выкл]
D3DCOLOR TColIsIn = DARK18; //Цвет текста    [IsInBox]
D3DCOLOR TColOn = DARK2; //Цвет текста    [Вкл]
D3DCOLOR EColOff = DARK10; //Цвет елементов  [Выкл]
D3DCOLOR EColIsIn = DARK12;//Цвет елементов  [IsInBox]
void  WF_XVTT(LPDIRECT3DDEVICE9 pDevice)
{
	lm = GetAsyncKeyState(VK_LBUTTON) & 1;
	flm = GetAsyncKeyState(VK_LBUTTON);


	DrawMenu(AS.GC.x, AS.GC.y, 400, 180, "General Menu", pDevice);
	Pircture(45, 40,pDevice);
	FolderButton(NOC.Title1, 250, 80, 3, Choose, 120, pDevice);
	if (Choose == 1)
	{
		AS.AIMC.bpos.y2 = 110 + 21 * 3;
		AS.GC.bpos.s1 = 130 + 21 * 3, AS.GC.bpos.s2 = AS.GC.bpos.s1 + 21, AS.GC.bpos.s3 = AS.GC.bpos.s2 + 22;
		//AddFolder_Button(250, 100, "Aim Folder", 120,Aim, pDevice); 
		AddFolder_Button(250, 100, "ESP&Aim Hack", 120,Player, pDevice);
		//AddFolder_Button(250, 121, "Dino Hack",120, Dino, pDevice);
		//AddFolder_Button(250, 142, "Weapon Hack", 120, weapon, pDevice);
	}
	else AS.AIMC.bpos.y2 = 110, AS.GC.bpos.s1 = 130, AS.GC.bpos.s2 = AS.GC.bpos.s1 + 20, AS.GC.bpos.s3 = AS.GC.bpos.s2 + 20;
	if (Aim == 1)
	{
		DrawMenu(AS.AIMC.x, AS.AIMC.y, 400, 180, "Aim Folder", pDevice);
	}
//	FolderButton(NOC.Title2, 250, AS.AIMC.bpos.y2, 3, Choose2, 120, pDevice);
	if (Player == 1)
	{
		DrawMenu(AS.ESPC.x, AS.ESPC.y, 180, 160, "ESP&Aim Hack", pDevice);
		Check(15, 330, "ESP Skelet", Fun.EspGM, pDevice);
		Check(15, 350, "Fast Aim", Fun.Aim, pDevice);
		

	}

	if (Dino == 1)
	{
		DrawMenu(AS.ESPC.x, AS.ESPC.y, 180, 160, "Dino Folder", pDevice);
		Check(15, 370, "Ультра Плевок", Fun.DinoFast, pDevice);
		Check(15, 390, "Дино пробеги[F5]", Fun.iDinoSpam, pDevice);
	}

	if (weapon == 1)
	{
		DrawMenu(AS.AIMC.x, AS.AIMC.y, 400, 180, "Weapon Hack", pDevice);
		Check(305, 330, "Swap Weapon", Fun.SwapWeapon, pDevice);
	}

}


