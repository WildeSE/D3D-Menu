#include "cDraw.h"

char* m2[5] = { "[ 0 ]", "[ 1 ]", "[ 2 ]", "[ 3 ]", "[ 4 ]" };
char* komand[2] = { "PVE/PVP", "Мясо" };
char* m3[3] = { "ЛКМ", "E", "L_ALT" };
char* AimON[2] = { "Голова", "Тело" };
char* MN[18] = { "[ 0 ]", "[ 1 ]", "[ 2 ]", "[ 3 ]", "[ 4 ]", "[ 5 ]", "[ 6 ]", "[ 7 ]", "[ 8 ]", "[ 9 ]", "[ 10 ]", "[ 11 ]", "[ 12 ]", "[ 13 ]", "[ 14 ]", "[ 15 ]", "[ 16 ]", "[ 17 ]" };

void _stdcall cDraw::SHOW_MENU(LPDIRECT3DDEVICE9  pDevice)
{
	Studio_Menu(20, 20, "D3D by MayLo", pDevice);
	Engine_Button(23, 51, Varm.Menu0, "Оружие", pDevice);
	Engine_Button(23, 51 + 28, Varm.Menu1, "ЕСП", pDevice);
	Engine_Button(23, 51 + 28 * 2, Varm.Menu2, "АИМ", pDevice);
	Engine_Button(23, 51 + 28 * 3, Varm.Menu4, "Магнит", pDevice);
	Engine_Button(23, 51 + 28 * 4, Varm.Menu3, "Прочее", pDevice);
	Engine_Button(23, 51 + 28 * 5, Varm.cvet, "Цвета ЕСП", pDevice);
    if (Varm.Menu0)
	{
		Engine_CheckBox(23, 51, Varm.отдача, "Нет отдачи", pDevice);
		Engine_CheckBox(23, 51 + 21, Varm.зам, "Нет разброса", pDevice);
		Engine_CheckBox(23, 51 + 21 * 2, Varm.Точность, "Точность", pDevice);
		Engine_CheckBox(23, 51 + 21 * 3, Varm.Точностьь, "Точность [100]", pDevice);
		Engine_CheckBox(23, 51 + 21 * 4, Varm.flash, "Нет cлепа", pDevice);
		Engine_CheckBox(23, 51 + 21 * 5, Varm.глуш, "Глушитель", pDevice);
		Engine_CheckBox(23, 51 + 21 * 6, Varm.bnojl, "Быстрый нож [ЛКМ]", pDevice);
		Engine_CheckBox(23, 51 + 21 * 7, Varm.bnojk, "Быстрый нож [ПКМ]", pDevice);
		Engine_Scroll(23, 51 + 21 * 8, Varm.Ckoroctrel2, m2, 4, "Темп стрельбы", pDevice);
	}
	if (Varm.Menu1)
	{
		Engine_CheckBox(23, 51, Varm.ESPSkel, "ESP Скелет", pDevice);
		Engine_CheckBox(23, 51 + 21, Varm.ESP_3D, "ESP Обводка", pDevice);
		Engine_CheckBox(23, 51 + 21 * 2, Varm.ESP_Dist, "ESP Дистанция", pDevice);
		Engine_CheckBox(23, 51 + 21 * 3, Varm.ESPName, "ESP Ники", pDevice);
		Engine_CheckBox(23, 51 + 21 * 4, Varm.Line, "ESP Линии", pDevice);
		Engine_CheckBox(23, 51 + 21 * 5, Varm.vzryv, "ESP Гранаты и мины", pDevice);
		Engine_CheckBox(23, 51 + 21 * 6, Varm.wp, "ESP Оружие", pDevice);
		Engine_Scroll(23, 51 + 21 * 7, Varm.tm, komand, 1, "Выбор команды", pDevice);
	}
	if (Varm.Menu2)
	{
		Engine_CheckBox(23, 51, Varm.OnAim, "Аимбот", pDevice);
		if (Varm.OnAim)
		{
			Engine_Scroll(23, 51 + 21, Varm.bon, AimON, 1, "Часть тела", pDevice);
			Engine_Scroll(23, 51 + 21 * 2, Varm.AimKey, m3, 2, "Кнопка аима", pDevice);
			Engine_CheckBox(23, 51 + 21 * 3, Varm.probiv, "Учёт защиты головы", pDevice);
			Engine_CheckBox(23, 51 + 21 * 4, Varm.NoAim, "Откл.Аимбота на боссов", pDevice);
			
		}
	}
	if (Varm.Menu4)
	{
		Engine_CheckBox(23, 51, Varm._fMag, "Магнит [CAPS_LOCK]", pDevice);
		if (Varm._fMag)
		{
			Engine_Scroll(23, 51 + 21, Varm._fMagX, MN, 17, "X:", pDevice);
			Engine_Scroll(23, 51 + 21 * 2, Varm._fMagY, MN, 17, "Y:", pDevice);
			Engine_Scroll(23, 51 + 21 * 3, Varm._fMagZ, MN, 17, "Z:", pDevice);
			Engine_CheckBox(23, 51 + 21 * 4, Varm.NoMG, "Откл.Магнита на боссов", pDevice);
		}
	}
	if (Varm.Menu3)
	{
		Engine_CheckBox(23, 51, Varm.бег, "Выносливость", pDevice);
		Engine_CheckBox(23, 51 + 21, Varm.подкат, "Длинный подкат", pDevice);
		Engine_CheckBox(23, 51 + 21 * 2, Varm.np, "Нет урона от падения", pDevice);
		Engine_CheckBox(23, 51 + 21 * 3, Varm.темь, "Темень мод", pDevice);
		Engine_CheckBox(23, 51 + 21 * 4, Varm.vzlet, "Взлет [V]", pDevice);
		Engine_CheckBox(23, 51 + 21 * 5, Varm.Kasper, "Каспер [Q]", pDevice);
		Engine_CheckBox(23, 51 + 21 * 6, Varm.sped, "Скорость бега [SHIFT]", pDevice);
		Engine_CheckBox(23, 51 + 21 * 7, Varm.vid3, "Вид от 3 лица [F1]", pDevice);
		Engine_CheckBox(23, 51 + 21 * 8, Varm.jump, "Высокий прыжок [X1]", pDevice);
	}
	if (Varm.cvet)
	{
		M1Chams(23, 51, "Цвет врага перед вами", Varm.ColorVisible, RED, GREEN, BLUE, Aqua, CHOCOLATE2, WHITE, ORANGE, PURPLE, GREY, GOLD2, pDevice);
		M1Chams(23, 51 + 21, "Цвет врага за стеной", Varm.ColorHiden, RED, GREEN, BLUE, Aqua, CHOCOLATE2, WHITE, ORANGE, PURPLE, GREY, GOLD2, pDevice);
		M1Chams(23, 51 + 21 * 2, "Цвет оружие", Varm.ColorHiden1, LIME, GREEN, BLUE, Aqua, CHOCOLATE2, RED, ORANGE, PURPLE, GREY, GOLD2, pDevice);
		M1Chams(23, 51 + 21 * 3, "Цвет гранаты и мины", Varm.ColorHiden2, LIME, GREEN, BLUE, Aqua, CHOCOLATE2, RED, ORANGE, PURPLE, GREY, GOLD2, pDevice);
	}
}

