//������ ����������
D3DCOLOR TColOff = DARK18; //���� ������    [����]
D3DCOLOR TColIsIn = DARK18; //���� ������    [IsInBox]
D3DCOLOR TColOn = DARK2; //���� ������    [���]
D3DCOLOR EColOff = DARK10; //���� ���������  [����]
D3DCOLOR EColIsIn = DARK12;//���� ���������  [IsInBox]


void _stdcall GoldBase(LPDIRECT3DDEVICE9 pDevice)
{
	lm = GetAsyncKeyState(VK_LBUTTON) & 1;
	rm = GetAsyncKeyState(VK_RBUTTON) & 1;
	flm = GetAsyncKeyState(VK_LBUTTON);
	frm = GetAsyncKeyState(VK_RBUTTON);


	if (Fun.Color1 == 1){ EColOn = BLUE; } 
	if (Fun.Color2 == 1){ EColOn = DARK10; }
	if (Fun.Color3 == 1){ EColOn = BLUEMAZAY; }
	if (Fun.Color4 == 1){ EColOn = BORDERCOLOR; }
	if (Fun.Color5 == 1){ EColOn = YELLOW; }
	if (Fun.Color6 == 1){ EColOn = GREEN; }
	
	DrawMenu(pDevice);
	Button(25, 45,"Hacks", Fun.Haks,  pDevice);
	Button(25,75,"ESP", Fun.esp,  pDevice);
	Button(25,105,"Player", Fun.Player,pDevice);
    Button(25,135,"�����", Fun.Test5,  pDevice);
	Text("[Wilde Hack]", 30, 215, WHITE, DT_LEFT | DT_NOCLIP);   

	if (Fun.Haks == 1)
	{
		
		DoubleCheck(130,45,"WallShoot", Fun.WallShoot, pDevice);
		DoubleCheck(130,65,"������� [�������]", Fun.AntiKick,pDevice);
		DoubleCheck(130,105,"����� 110 HP", Fun.kupon110xp, pDevice);
		DoubleCheck(130,85,"���.����", Fun.resp, pDevice);
		DoubleCheck(130,125,"���� ����� ��� �������", Fun.jump, pDevice);
		DoubleCheck(130,145,"Jump", Fun.prizok, pDevice);
		DoubleCheck(130,165,"GM ���", Fun.GM, pDevice);
		DoubleCheck(130,185,"�����������", Fun.reload, pDevice);
		DoubleCheck(130,205,"���� ������", Fun.AO, pDevice);
		DoubleCheck(130,225,"Aim", Fun.Aim, pDevice);
		
		
		
		  
	

	}

	

	if (Fun.esp == 1)
	{
		
		Check(350,45,"ESP GM",Fun.EspGM,  pDevice );
		
	
	}

	if (Fun.Test4 == 1)
	{

	    DoubleCheckColor(35,80,"Orange", Fun.Color1, pDevice);
		DoubleCheckColor(35,105,"LightBlue", Fun.Color4,pDevice);
		DoubleCheckColor(35,130,"Yellow", Fun.Color5, pDevice);
		DoubleCheckColor(35,155,"Green", Fun.Color6,pDevice);
	}

	if (Fun.Test5 == 1)
	{
		Text("����������:", 130, 70, EColOn, DT_LEFT | DT_NOCLIP);
		Text("������:0.0.2", 130, 85, GREEN, DT_LEFT | DT_NOCLIP);
		Text("����������� [Wilde] ���������� ��� pbhack.ru ",130,100,GREEN,DT_LEFT|DT_NOCLIP);
		Text("����� ������� �������� ������� F3",130,115,GREEN,DT_LEFT|DT_NOCLIP);
	}
}



