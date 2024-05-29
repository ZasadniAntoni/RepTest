
#include "led.h"
#include "keyboard.h"
#include "timer.h"

#define Delay 100000 // 10^5

int main(){
	LedInit();
	KeyboardInit();
	//InitTimer0();
	InitTimer0Match0(Delay);
	
	while(1)
	{
		//WaitOnTimer0(Delay);
		WaitOnTimer0Match0();
		LedStepLeft();
	}
}
// gittestmz