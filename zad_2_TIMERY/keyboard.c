#include <LPC21xx.H>

#define S0_bm (1<<4) //0x10
#define S1_bm (1<<6) //0x40
#define S2_bm (1<<5) //0x20
#define S3_bm (1<<7) //0x80

void KeyboardInit()
{
	IO0DIR = IO0DIR & (~(S0_bm|S1_bm|S2_bm|S3_bm));
}

enum KeyboardState {RELEASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

enum KeyboardState eKeyboardRead()
{
	if((IO0PIN & S0_bm) == 0)
		{
		return BUTTON_0;
		}
	if((IO0PIN & S1_bm) == 0)
		{
		return BUTTON_1;
		}
	if((IO0PIN & S2_bm) == 0)
		{
		return BUTTON_2;
		}
	if((IO0PIN & S3_bm) == 0)
		{
		return BUTTON_3;
		}
	else
		{
		return RELEASED;
		}
}

