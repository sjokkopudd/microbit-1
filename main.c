#include <stdint.h>
#include <stdio.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	int sleep = 0;
	while(1){

		if (!(GPIO->IN&(1 << 26)))
		{
		 for (int high = 13; high < 16; high++)
		 {
		 	GPIO->OUTSET = (1 << high);
		 }
		 for (int low = 4; low < 13; low++)
		 {
		 	GPIO->OUTCLR = (1 << low);
		 }
		}


		if (!(GPIO->IN&(1 << 17)))
		{
		 for (int high = 13; high < 16; high++)
		 {
		 	GPIO->OUTCLR = (1 << high);
		 }
		 for (int low = 4; low < 13; low++)
		 {
		 	GPIO->OUTSET = (1 << low);
		 }
		}

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
