/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../GLCD/GLCD.h" 
#include "../timer/timer.h"
#include "../spostamento/spostamento.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


volatile int pause =0, prima=0;
extern uint8_t state, score1, score2, ultimorimbalzo, val2;
extern int perso, punto, aggiornato, oldval, oldval2,mossa , direzione2, aggiornato2;
uint8_t key1 = 0;
uint8_t key2 = 0;
uint8_t int0 = 0;

void RIT_IRQHandler (void)
{		int i=0;

		if(key1!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	/* KEY1 pressed */
			key1++;				
			switch(key1){
				case 2:		 //premo key1 -> start
					reset_timer(0); 
					reset_timer(1);
					GUI_Text(45, 152, (uint8_t *) "Press key1 to start", Black, Black);
				
				
					enable_timer(0);
					enable_timer(1);
				
					for(i=0;i<5;i++){ //bande
						LCD_DrawLine(0+i,0,0+i,320, Red);
						LCD_DrawLine(239-i,0,239-i,320, Red);
					}
					
					for(i=0;i<10;i++){  //nuovo puddle
					 LCD_DrawLine(100,298-i,100+40,298-i, Green);
					 prima=1;
					}
				

				if(punto==1){
					disable_timer(0);
					disable_timer(1);
					reset_timer(0); 
					reset_timer(1);
				  punto=0;
				}
				if (punto==0){
					enable_timer(0);
					enable_timer(1);
				}
					break;
				default:
					break;
			}
		}	else {	/* button released */
			key1=0;	
			NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		}
//		LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
//		return;
	}
		
		if(key2!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	/* KEY2 pressed */
			key2++;				
			switch(key2){
				case 2:	
					if(pause==0){
						GUI_Text(100, 160, (uint8_t *) "Pause", White, Black);
						GUI_Text(40, 175, (uint8_t *) "Press key2 to resume", White, Black);
					  pause=1;
						disable_timer(0);
						disable_timer(1);
						reset_timer(0);
						reset_timer(1);
					  }else{ //quando lo pigio di nuovo
						GUI_Text(100, 160, (uint8_t *) "Pause", Black, Black);
						GUI_Text(40, 175, (uint8_t *) "Press key2 to resume", Black, Black);
						enable_timer(0);
						enable_timer(1);		
						pause = 0;
					}
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			key2=0;		
			NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
		}
//		LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
//		return;
 }	
	if(int0!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){	/* INT1 pressed */
			int0++;				
			switch(int0){
				case 2:	
					if(perso == 1){
						reset_timer(0);
						disable_timer(0);
						LCD_Clear(Black);
						GUI_Text(45, 152, (uint8_t *) "Press Key1 to start", White, Black);			
						perso=0;
						pause=0;
						score1=0;
						score2=0;
						ultimorimbalzo=0;
						val2=190;
						punto=0;
						mossa=0;
						direzione2=0;
						aggiornato=0;
						aggiornato2=0;
						NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
		
					}else{
						LCD_Clear(Black);
						GUI_Text(90, 152, (uint8_t *) "Error", White, Black);
						reset_timer(0);
						disable_timer(0);
						pause=0;
					
				}
					break;
					default:
					break;
			}
		}
		else {	/* button released */
			int0=0;	
			NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/	
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
//		LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
//		return;
	}

  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
}

/******************************************************************************
**                            End Of File
******************************************************************************/
