#ifndef _GAMECLASS_H_
#define _GAMECLASS_H_

enum mBones
{
	groin		=	0,
	groin2		=	1,
	stomach		=	2,
	stomach2	=	3,
	body		=	4,
	chest		=	5,
	neck		=	6,
	head		=	7,
	left_foot	=	8,
	right_foot	=	9,
	left_cubit	=	10,
	right_cubit =	11,
	left_hip	=	12,
	right_hip	=	13,
	left_knee	=	14,
	right_knee	=	15,
};
void drawSkeleton(int iSlot, DWORD Color, LPDIRECT3DDEVICE9 pDevice)
{
	drawBone(iSlot,groin,groin2,Color,pDevice);
	drawBone(iSlot,groin2,stomach,Color,pDevice);
	drawBone(iSlot,stomach,stomach2,Color,pDevice);
	drawBone(iSlot,stomach2,body,Color,pDevice);
	drawBone(iSlot,body,chest,Color,pDevice);
	drawBone(iSlot,chest,neck,Color,pDevice);
	drawBone(iSlot,neck,head,Color,pDevice);
	drawBone(iSlot,left_hip,right_hip,Color,pDevice);
	drawBone(iSlot,left_hip,left_knee,Color,pDevice);
	drawBone(iSlot,left_knee,left_foot,Color,pDevice);
	drawBone(iSlot,right_hip,right_knee,Color,pDevice);
	drawBone(iSlot,right_knee,right_foot,Color,pDevice);
	drawBone(iSlot,neck,left_cubit,Color,pDevice);
	drawBone(iSlot,neck,right_cubit,Color,pDevice);
}

#endif 