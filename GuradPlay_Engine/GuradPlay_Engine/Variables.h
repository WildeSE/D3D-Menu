#pragma once
struct cGPEngine
{
    //Buttons
	bool Menu1,
		 Menu2,
		 Menu3,
		 Menu4,
		 Menu5,
		 Menu6;
	//������:
	bool NoRecoil,
		 Acuraccy,
		 NoReload,
		 AutoShot,
		 RapidFire,
		 NotBrokenWeapons,
		 SuperSniper;

	//�����:
	bool AirJump,
		 NFD,
		 NoKick;
	//���
	bool FastAim,
		 VectorAim,
		 ���,
	  	 Skeleton,
		 Line,
		 HP,
		 Box,
		 Distance,
		 Name;
	int SpeedHack,
		JumpHack,
		ZoomHack;
};
extern cGPEngine GPEngine;