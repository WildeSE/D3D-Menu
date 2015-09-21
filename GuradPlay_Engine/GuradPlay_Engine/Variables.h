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
	//Оружее:
	bool NoRecoil,
		 Acuraccy,
		 NoReload,
		 AutoShot,
		 RapidFire,
		 NotBrokenWeapons,
		 SuperSniper;

	//Игрок:
	bool AirJump,
		 NFD,
		 NoKick;
	//аим
	bool FastAim,
		 VectorAim,
		 Ноч,
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