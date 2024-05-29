#include <LPC21xx.H>

#define COUNTER_ENABLE_bm (1<<0) //0x1
#define COUNTER_RESET_bm (1<<1) //0x2

#define INTERRUPT_ON_MATCH_MR0_bm (1<<0) //0x1
#define RESET_ON_MATCH_MR0_bm (1<<1) //0x2
#define MR0_INTERRUPT_FLAG_bm (1<<0) //0x1

void InitTimer0()
{
	T0TCR = COUNTER_ENABLE_bm;		//wlaczenie Timera
}

void WaitOnTimer0(unsigned int uiTime)
{
	T0TCR = T0TCR | COUNTER_RESET_bm;		//resetowanie Timera
	T0TCR = T0TCR & (~COUNTER_RESET_bm);		//zatrzymanie resetowania Timera (zeby wartosc licznika Timera nie byl ciagle resetowany)
	
	while(T0TC < (uiTime * 15))		//co zrobic zeby mozna bylo dac !=?		zmniejszenie ilosci dzialan w porownaniu/spowolnienie Timera (zmniejszenie czestotliwosci zegara peryferiow)
	{}
}

void InitTimer0Match0(unsigned int uiDelayTime){
	T0MR0 = (uiDelayTime * 15);		//wpisanie wartosci do rejestru porownujacego
	
	T0TCR = T0TCR | COUNTER_RESET_bm;		//resetowanie Timera
	T0TCR = T0TCR & (~COUNTER_RESET_bm);		//zatrzymanie resetowania Timera
	T0TCR = T0TCR | COUNTER_ENABLE_bm;		//wlaczenie Timera
	
	T0MCR = T0MCR | INTERRUPT_ON_MATCH_MR0_bm;		//generacja przerwania w momencie T0TC = T0MR0
	T0MCR = T0MCR | RESET_ON_MATCH_MR0_bm;		//zresetowanie wartosci licznika w momencie T0TC = T0MR0
}

void WaitOnTimer0Match0(void){
	while ((T0IR & MR0_INTERRUPT_FLAG_bm) == 0)		//czekanie dopoki pojawi sie przerwanie 
	{}
	T0IR = MR0_INTERRUPT_FLAG_bm;		//zresetowanie flagi przerwania; suma bitowa nie jest tu potrzebna bo "Writing a zero has no effect."
} //111 | 001 = 111 ; MR0..MR2 generuja przerwanie -> chcac zresetowac tylko flage przerwania MR0 przez sume logiczna usunie tez z flagi MR1, MR2


// "Writing a logic one to the corresponding IR bit will reset the interrupt. Writing a zero has no effect."
