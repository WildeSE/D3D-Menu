#pragma once
#include "cRender.h"


#define MAIN_ITEM 9

class cMenu :public cRender
{
public:
	cMenu(){};
	~cMenu(){};

	struct sItemMenu
	{
		int x, y;
		int CtrlY;
	};
	sItemMenu ItemMenu;


	void InitializeMenu(int x, int y, char *Titl);
	void ShowMenu();
	void Item_Button(char* text);

	BOOL State_Key(int Key, DWORD dwTimeOut);
	BOOL IsInBox(int x, int y, int w, int h);
private:
	int ButWidth;
	int x, y;
	char *Titl;
};
extern cMenu*Menu;

static struct _Keys{ bool bPressed;  DWORD dwStartTime; }kPressingKeys[256];




enum Colors : D3DCOLOR
{
	white = 0xffffffff,
	black = 0xff000000,
	aqua_marin = 0xff7fffd4,
	red = 0xffff0000,
	green = 0xff00ff00,
	blue = 0xff0000ff,
	//¤ркие цвета
	vivid_red = 0xffff2400,
	vivid_green = 0xff66ff00,
	vivid_cian = 0xff00ffff,
	//темные цвета
	DarkBlue = 0xFF00008B,
	DarkGray = 0xFFA9A9A9,
	DarkGreen = 0xFF006400,
	DarkOrange = 0xFFFF8C00,
	DarkRed = 0xFF8B0000,
	DarkSeaGreen = 0xFF8FBC8B,
	DarkSlateBlue = 0xFF483D8B,
	DarkSlateGray = 0xFF2F4F4F,

	Navy = 0xFF000080,
	OldLace = 0xFFFDF5E6,
	Olive = 0xFF808000,
	OliveDrab = 0xFF6B8E23,
	Orange = 0xFFFFA500,
	OrangeRed = 0xFFFF4500,
	Orchid = 0xFFDA70D6,
	PaleGoldenrod = 0xFFEEE8AA,
	PaleGreen = 0xFF98FB98,
	PaleTurquoise = 0xFFAFEEEE,
	PaleVioletRed = 0xFFDB7093,
	PapayaWhip = 0xFFFFEFD5,
	PeachPuff = 0xFFFFDAB9,
	Peru = 0xFFCD853F,
	Pink = 0xFFFFC0CB,
	Plum = 0xFFDDA0DD,
	PowderBlue = 0xFFB0E0E6,
	RosyBrown = 0xFFBC8F8F,
	RoyalBlue = 0xFF4169E1,
	SaddleBrown = 0xFF8B4513,
	Salmon = 0xFFFA8072,
	SandyBrown = 0xFFF4A460,
	SeaGreen = 0xFF2E8B57,
	SeaShell = 0xFFFFF5EE,
	Sienna = 0xFFA0522D,
	Silver = 0xFFC0C0C0,
	SkyBlue = 0xFF87CEEB,
	SlateBlue = 0xFF6A5ACD,
	SlateGray = 0xFF708090,
	Snow = 0xFFFFFAFA,
	SpringGreen = 0xFF00FF7F,
	SteelBlue = 0xFF4682B4,
	Tan = 0xFFD2B48C,
	Teal = 0xFF008080,
	Thistle = 0xFFD8BFD8,
	Tomato = 0xFFFF6347,
	Transparent = 0x00FFFFFF,
	Turquoise = 0xFF40E0D0,
	Violet = 0xFFEE82EE,
	Wheat = 0xFFF5DEB3,
	WhiteSmoke = 0xFFF5F5F5,
	YellowGreen = 0xFF9ACD32
};
