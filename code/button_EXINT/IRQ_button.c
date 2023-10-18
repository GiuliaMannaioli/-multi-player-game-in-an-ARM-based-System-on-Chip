#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"
#include "../RIT/RIT.h"		  

extern uint8_t key1;
extern uint8_t key2;
extern uint8_t int0;

void EINT0_IRQHandler (void)	    //int0
{

	enable_RIT();	
	NVIC_DisableIRQ(EINT0_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* GPIO pin selection */
	int0=1;		
  LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}
void EINT1_IRQHandler (void)	  //key1
{
	enable_RIT();										/* enable RIT to count 50ms			--> timer che controlla ogni 50ms	 */
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	key1=1;
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}
void EINT2_IRQHandler (void)	  
{
	enable_RIT();										/* enable RIT to count 50ms			--> timer che controlla ogni 50ms	 */
	NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 24);     /* GPIO pin selection */
	key2=1;
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}
