#include <LPC21xx.H>

#define LED0_bm (1<<16) //0x10000
#define LED1_bm (1<<17) //0x20000
#define LED2_bm (1<<18) //0x40000
#define LED3_bm (1<<19) //0x80000

void LedInit()
{
	IO1DIR |= (LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks)
{
	IO1CLR = (LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	
	switch(ucLedIndeks)
	{
		case 0:
			IO1SET = LED0_bm;
			break;
		case 1:
			IO1SET = LED1_bm;
			break;
		case 2:
			IO1SET = LED2_bm;
			break;
		case 3:
			IO1SET = LED3_bm;
			break;
	}
}

enum StepDirection {LEFT, RIGHT};

void LedStep(enum StepDirection eStepDirection)
{
	static unsigned int uiStepCounter = 0;
	
	if(eStepDirection == LEFT)
	{
		uiStepCounter++;
		LedOn(uiStepCounter % 4);
	}
	if(eStepDirection == RIGHT)
	{
		uiStepCounter--;
		LedOn(uiStepCounter % 4);
	}
}

void LedStepLeft()
{
	LedStep(LEFT);
}

void LedStepRight()
{
	LedStep(RIGHT);
}

