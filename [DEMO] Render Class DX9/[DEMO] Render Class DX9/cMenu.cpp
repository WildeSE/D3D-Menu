#include "cMenu.h"

D3DCOLOR color_But = 0xff282828,
         color_Text_Contrl = aqua_marin,
		 color_Bord = black,
		 color_InBut = vivid_green,
		 color_fon = DarkSlateGray,
		 color_Text_Title = vivid_green;



void cMenu::InitializeMenu(int x, int y, char *Titl)
{
	this->Titl = Titl;
	this->x = x;
	this->y = y;

	(ItemMenu).x = x;
	(ItemMenu).y = y + 22;

	ButWidth = 120;
	Render.render_Box(this->x, this->y, ButWidth, 20, DarkSlateGray);
	Render.render_Border(this->x, this->y, ButWidth, 20, 1, black);
	Render.render_String(this->x + ButWidth / 2, this->y + 3, vivid_green, DT_CENTER, this->Titl);

	ShowMenu();

}


int Button_Mass[MAIN_ITEM] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    Button_Number = 0,
    Button_Max = 0;



BOOL  cMenu::State_Key(int Key, DWORD dwTimeOut)
{
	if (HIWORD(GetKeyState(Key)))
	{
		if (!kPressingKeys[Key].bPressed || (kPressingKeys[Key].dwStartTime && (kPressingKeys[Key].dwStartTime + dwTimeOut) <= GetTickCount()))
		{
			kPressingKeys[Key].bPressed = TRUE;
			if (dwTimeOut > NULL)
				kPressingKeys[Key].dwStartTime = GetTickCount();
			return TRUE;
		}
	}
	else
		kPressingKeys[Key].bPressed = FALSE;
	return FALSE;
}
BOOL  cMenu::IsInBox(int x, int y, int w, int h)
{
	POINT MousePosition;
	GetCursorPos(&MousePosition);
	ScreenToClient(GetForegroundWindow(), &MousePosition);
	return(MousePosition.x >= x && MousePosition.x <= x + w && MousePosition.y >= y && MousePosition.y <= y + h);
}
void  cMenu::Item_Button(char* text)
{
	int x = (ItemMenu).x,
		y = (ItemMenu).y,
		h = 22,
		w = ButWidth;


	D3DCOLOR in_mause_pos = color_But;
	Render.render_Box(x, y, w, h, color_But);

	if (IsInBox(x, y, w, h))
	{
		in_mause_pos = color_InBut;
		if (State_Key(VK_LBUTTON, 30))
		{
			if (Button_Mass[Button_Number] != 1)
				Button_Mass[Button_Number] = 1;
		}
	}


	if (Button_Mass[Button_Number])
	{
		

		in_mause_pos = vivid_red;
		for (int i = 0; i < MAIN_ITEM; i++)
		if (i != Button_Number)
			Button_Mass[i] = 0;
	}

	Render.render_Box(x, y, 4, h, in_mause_pos);
	Render.render_Border(x, y, w, h, 1, color_Bord);
	Render.render_Border(x, y, 4, h, 1, color_Bord);
	Render.render_String(x + (w / 2), y + 4, color_Text_Contrl, DT_CENTER, text);


	Button_Number = Button_Number + 1;

	if (Button_Max < Button_Number)
		Button_Max = Button_Number;

	(ItemMenu).y = y + 20;
}