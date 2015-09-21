#include "cDraw.h"

void _fastcall  cDraw::SHOW_MENU(LPDIRECT3DDEVICE9  pDevice)
{
	Engine_Box(8,8,220,140,Fon_Col,pDevice);
	Engine_Border(8,8,220,20,1,Elm_Col,pDevice);
	Engine_Border(8,8,220,140,1,Elm_Col,pDevice);
	Engine_Text(12,10, Голубой, "System Bot Wilde and iDreeM", L_Text);
	Engine_Text(12,30, Tex_Col, "Анти Отдача         - [NUMPAD 0]", L_Text);
	Engine_Text(12,50, Tex_Col, "АнтиРазброс         - [NUMPAD 1]", L_Text);
	Engine_Text(12,70, Tex_Col, "Фаст.Релоад         - [NUMPAD 2]", L_Text);
	Engine_Text(12,90, Tex_Col, "AntiBroken           - [NUMPAD 3]", L_Text);
	Engine_Text(12,110, Tex_Col,"FrezePlayer          -       [E]", L_Text);
    Engine_Text(12,130, Tex_Col,"Скорострел.         - [NUMPAD 4]", L_Text);
}
