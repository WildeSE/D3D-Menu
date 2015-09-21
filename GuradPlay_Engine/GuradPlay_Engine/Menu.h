#include "cDraw.h"
char *Values  [101] = { "0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100"};
char *Values1  [31] = { "1.0","1.1","1.2","1.3","1.4","1.5","1.6","1.7","1.8","1.9","2.0","2.1","2.2","2.3","2.4","2.5","2.6","2.7","2.8","2.9","3.0","3.1","3.2","3.3","3.4","3.5","3.6","3.7","3.8","3.9","4.0"};
char *Values2  [26] = { "0","2","4","6","8","10","12","14","16","18","20","22","24","26","28","30","32","34","36","38","40","42","44","46","48","50"};

void  cDraw::SHOW_MENU(LPDIRECT3DDEVICE9  pDevice)
{
	Engine_MenuTitle(20, 20, "Guard Play Engine Dx9", pDevice);
	Engine_ButtonFloder(20,20,3, pDevice);

	Engine_Button(25,49,GPEngine.Menu1,"- Оружее",pDevice);//GPEngine.FastAim
    Engine_Button(25,49+30,GPEngine.Menu2,"- Игрок",pDevice);
	Engine_Button(25,49+30*2,GPEngine.Menu3,"- Esp",pDevice);
	Engine_Button(25,49+30*3,GPEngine.Menu6,"Информация",pDevice);

	if(GPEngine.Menu1)
	{
		Engine_FunctionFloder(20,20,6,pDevice);
		Engine_DoubleCheck(175, 50,GPEngine.NoRecoil,"- No Recoil", pDevice);
		Engine_DoubleCheck(175, 50+22,GPEngine.Acuraccy,"- Acuraccy", pDevice);
		Engine_DoubleCheck(175, 50+22*2,GPEngine.NoReload,"- No Reload", pDevice);
		Engine_DoubleCheck(175, 50+22*3,GPEngine.AutoShot,"- Auto Shot", pDevice);
		Engine_DoubleCheck(175, 50+22*4,GPEngine.NotBrokenWeapons,"- Not Broken Weapons", pDevice);
		Engine_CheckBox(175, 50+22*5, GPEngine.RapidFire,"- Rapid Fire", pDevice);
		Engine_CheckBox(175, 50+22*6, GPEngine.SuperSniper,"- Super Sniper", pDevice);
	}
	if(GPEngine.Menu2)
	{
		Engine_FunctionFloder(20,20,4,pDevice);

		Engine_DoubleCheck(175, 50,GPEngine.AirJump,"- Air Jump",  pDevice);
		Engine_DoubleCheck(175, 50+22,GPEngine.NFD,"- No Fall Damage",  pDevice);
		Engine_Scroll(175,50+22*2,GPEngine.SpeedHack,Values1,20,"- SpeedHack",  pDevice);
		Engine_Scroll(175,50+22*3,GPEngine.JumpHack,Values1,10,"- Height Jump",  pDevice);
		Engine_CheckBox(175, 50+22*4, GPEngine.NoKick,"- AntiKick.K", pDevice);
		//Engine_Scroll(175,50+22*4,GPEngine.ZoomMode,Values,3,   "- Engine Scroll",  pDevice);
		//Engine_Scroll(175,50+22*5,GPEngine.RapidFire,Values,3,  "- Engine Scroll",  pDevice);
	}
	if(GPEngine.Menu3)
	{
		Engine_FunctionFloder(20,20,6,pDevice);

		Engine_DoubleCheck(175, 50,GPEngine.Skeleton,"- Esp Skelet",  pDevice);
		Engine_DoubleCheck(175, 50+22,GPEngine.Line,"- Esp Line",  pDevice);
		Engine_DoubleCheck(175, 50+22*2,GPEngine.HP,"- Esp HP",  pDevice);
		Engine_DoubleCheck(175, 50+22*3,GPEngine.Box,"- Esp Box 2D",  pDevice);
		Engine_DoubleCheck(175, 50+22*4,GPEngine.Name,"- Esp String Ники и ХП",  pDevice);
		Engine_DoubleCheck(175, 50+22*5,GPEngine.Distance,"- Esp String Distance",  pDevice);
		Engine_DoubleCheck(175, 50+22*6,GPEngine.Ноч,"- Прибор ночного виденья тип",  pDevice);//GPEngine.Ноч
	}
	if(GPEngine.Menu6)
	{
		Engine_FunctionFloder(20,20,4,pDevice);

		Engine_Text(175, 50, Red, "- Платформа: Guard Play Engine", L_Text);
		Engine_Text(175, 50+22, Blue, "- Разработчик: iDReeM", L_Text);
		Engine_Text(175, 50+22*2, Blue, "- Копирайт1: GuradPlay.ru", L_Text);
		Engine_Text(175, 50+22*3, White, "- Копирайт2: PBHack.ru", L_Text);
		Engine_Text(175, 50+22*4, White, "- Скрыть|Открыть меню на END", L_Text);
	}
}
