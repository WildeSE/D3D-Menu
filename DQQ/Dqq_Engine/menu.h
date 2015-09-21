#include "cDraw.h"

char *ItemScroll  [11] = { "0","10","20","30","40","50","60","70","80","90","100"};
char *SizeMin  [40] = { "0.1","0.2","0.3","0.4","0.5","0.6","0.7","0.8","0.9","1.0","1.1","1.2","1.3","1.4","1.5","1.6","1.7","1.8","1.9","2.0","2.1","2.2","2.3","2.4","2.5","2.6","2.7","2.8","2.9","3.0","3.1","3.2","3.3","3.4","3.5","3.6","3.7","3.8","3.9","4.0"};
int sp = 4;
void  cDraw::SHOW_MENU(LPDIRECT3DDEVICE9  pDevice)
{
	Draw_Menu(15, 15, pDevice);

	if(Var.Weapon)
	{
		Draw_Button_Check(15, 15, Var.NoRecoil, "Отключить Отдачу", pDevice);//+
		Draw_Button_Check(15, 15+20, Var.Acuraccy, "Увеличить Точность", pDevice);//+
		Draw_Button_Check(15, 15+20*2, Var.NoReload, "Отключить Перезарядку", pDevice);//+
		Draw_Button_Check(15, 15+20*3, Var.AutoShot, "Автоматический Выстрел", pDevice);//+
		Draw_Button_Check(15, 15+20*4, Var.Rate, "Увеличить Скорострельность", pDevice);//+
		Draw_Button_Check(15, 15+20*5, Var.NoBrokenWeapon, "Нет Поломки Оружия", pDevice);//+
		Draw_Button_Check(15, 15+20*6, Var.LockPricel, "Блокировка Прицела", pDevice);
		Draw_Space(23+20*6, pDevice);//оранжевая перегородка
		Draw_Button_Check(15, 15+20*7+sp, Var.SuperSniper, "Cупер Снайперка", pDevice);//+
		Draw_Button_Check(15, 15+20*8+sp, Var.ShotIsOs, "Выстрел по Оси", pDevice);
		Draw_Button_Check(15, 15+20*9+sp, Var.AntiZV, "Anti ZV", pDevice);
	}
	if(Var.Player)
	{
		Draw_Button_Check(15, 15, Var.AirJump, "Прыжок в Воздухе", pDevice);//+
		Draw_Button_Check(15, 15+20, Var.NFD, "Нет Урона Падения", pDevice);//+
		Draw_Button_Check(15, 15+20*2, Var.AntiKick, "АнтиКик из Комнаты", pDevice);//+
		Draw_Button_Check(15, 15+20*3, Var.Hover, "Ховер [N]", pDevice);//+
		Draw_Button_Check(15, 15+20*4, Var.WallShot, "Wall Shot DINO [E]", pDevice);
		Draw_Button_Check(15, 15 + 20 * 5, Var.Aim, "Wall Shot DINO [E]", pDevice);
		Draw_Space(23+20*4, pDevice);//оранжевая перегородка
		Draw_Button_Scroll(15, 15+20*6+sp, Var.SpeedHack, ItemScroll, 10, "SpeedHack", pDevice);//+
		Draw_Button_Scroll(15, 15+20*7+sp, Var.UpJump, ItemScroll, 10, "Высота Прыжка", pDevice);//+
	}
	if(Var.Cupons)
	{
		Draw_Button_Check(15, 15, Var.CuponReload, "Купон Перезарядка -40%", pDevice);
		Draw_Button_Check(15, 15+20, Var.CuponResp, "Купон Респаун -50%", pDevice);
		Draw_Button_Check(15, 15+20*2, Var.CuponHP5, "Купон +5ХП", pDevice);
		Draw_Button_Check(15, 15+20*3, Var.CuponHP10, "Купон +10ХП", pDevice);
		Draw_Button_Check(15, 15+20*4, Var.CuponAddGerna, "Купон +1 Боезапас", pDevice);
		Draw_Space(23+20*4, pDevice);//оранжевая перегородка
	}
	if(Var.Visual)
	{
		Draw_Button_Check(15, 15, Var.WallHack, "WallHack", pDevice);
		Draw_Button_Check(15, 15+20, Var.CrossHair, "Рисовать Прицел", pDevice);
		Draw_Button_Check(15, 15+20*2, Var.NoFlash, "Нет Слепа", pDevice);
	}
	if(Var.Info)
	{
		Draw_Text(230, 25, Grey," Данный чит разработан специально для онлайн шутера PointBlank.\n Авторы: iDReeM и Dqq\n Copyright: PBHack.ru & GuardPlay.ru\n Версия Чита: 0.0.3\n Дата Обновления: 16.11.14", L_Text);
	}
	Draw_Box(219, 18, 7, 286, RedTwo, pDevice);
	
	Draw_Button(15, 15, Var.Weapon, "Меню Оружия", pDevice);
	Draw_Button(15, 15+25, Var.Player, "Меню Игрока", pDevice);
	Draw_Button(15, 15+25*2, Var.Cupons, "Меню Купонов", pDevice);
	Draw_Button(15, 15+25*3, Var.Visual, "Меню Визуального", pDevice);
	Draw_Button(15, 15+25*4, Var.Info, "Меню Информации", pDevice);

}