/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <stdio.h>
#include "LPC17xx.H"   /* LPC17xx definitions                */
#include "timer.h"
#include "../led/led.h"
#include "../GLCD/GLCD.h"
#include "../spostamento/spostamento.h"
#include "../adc/adc.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


extern uint8_t state;
extern unsigned short val ;
extern int oldball_i, oldball_j, pause;
volatile int ultimorimbalzo=0, perso=0, val2=190, punto=0;
volatile int indice_i=2, indice_j=2, c=0, d=0;
volatile uint8_t score1 = 0, score2 = 0;
volatile int mossa=0, num=0, direzione2=0;
int volte=0;


void TIMER0_IRQHandler (void)
{
char str1[2];
char str2[2];
 
	ADC_start_conversion();
	
if(pause==0){  

		  sprintf(str1, "%d", score1);
			sprintf(str2, "%d", score2);
			GUI_Text(6, 160, (uint8_t *) str1 , White, Black); //score1
			GUI_TextInverse(232, 176, (uint8_t *) str2 , White, Black); //score2
			
			if(mossa==0){
			indice_i=2;
			indice_j=2;
			mossa=3;
			}
			//else if(mossa!=0){
			LCD_DrawBall(oldball_i,oldball_j,Black); //ELIMINO PALLINA VECCHIA
				
		//	if((mossa==5 && perso==0) || (punto==1 && mossa==5 )) mossa=0;
			if(punto==1 && mossa==5 ) mossa=0;
		
			if(oldball_i-2<7 && mossa == 4){ //se sbatte a sx dal basso 
			mossa=1;
			
			ultimorimbalzo=oldball_j;
			}
			if(oldball_i-2<7 && mossa == 3){ //se sbatte a sx dall'alto 
			mossa=2;
		
			ultimorimbalzo=oldball_j; 
			}
			if(oldball_j-2<7 && mossa == 1){ //sbatte in alto da sx
			mossa=2;
			ultimorimbalzo=oldball_j;
			}
			if(oldball_j-2<7 && mossa == 4){ //sbatte in alto da dx
			mossa=3;
			ultimorimbalzo=oldball_j;
			}
			if(oldball_i+2>232&& mossa == 2){ //sbatte a dx dall'alto
			mossa=3;
			ultimorimbalzo=oldball_j;
			}
			if(oldball_i+2>232&& mossa == 1){ //sbatte a dx dal basso
			mossa=4; 
			ultimorimbalzo=oldball_j;
			}
			
			if(oldball_j+2>285){
					if((oldball_i-2>=val) && (oldball_i+2<=val+40)){ 
						if(ultimorimbalzo<120){ //se la palla rimbalza sulla parte superiore farà un angolo di 60 gradi dal paddle 
							indice_i=1;
							indice_j=2;
						}else if(ultimorimbalzo>200){ //se rimbalza nella parte inferiore farà un angolo di 30 gradi sul paddle 
							indice_i=2;
							indice_j=1;
						}
						if(mossa==3){//se sbatte sul paddle da dx 
							mossa=4;
								//devo cambiare indice_i e indice_j in base a dove va
							}else if(mossa==2){//se sbatte sul paddle da sx
							mossa=1;
							}
						}else if(((oldball_i-2<val) && (oldball_i+2>=val)) ||((oldball_i-2<=val+40) && (oldball_i+2>val+40))){
						//rimbalza in modo strano solo se colpisce gli angoli 
							indice_i=2;
							indice_j=1;
							if(mossa==3){//se sbatte sul paddle da dx 
							mossa=4;
							}else if(mossa==2){//se sbatte sul paddle da sx
							mossa=1;
							}
						} 
						if(oldball_j+2==288 || oldball_j+1==288){//esce sotto e prende un punto il player2
							 score2=score2+1;	
							 punto=1;
							 mossa=5;
					
						}
				}
				if(oldball_j-2<35){
							if((oldball_i-2>=val2) && (oldball_i+2<=val2+40)){ 
											if(ultimorimbalzo>200){ //se la palla rimbalza sulla parte inferiore farà un angolo di 60 gradi dal paddle 
												indice_i=1;
												indice_j=2;
											}else if(ultimorimbalzo<120){ //se rimbalza nella parte superiore farà un angolo di 30 gradi sul paddle 
												indice_i=2;
												indice_j=1;
											}
											if(mossa==4){//se sbatte sul paddle da dx 
												mossa=3;
													//devo cambiare indice_i e indice_j in base a dove va
												}else if(mossa==1){//se sbatte sul paddle da sx
												mossa=2;
												}
											}else if(((oldball_i-2<val2) && (oldball_i+2>=val2)) ||((oldball_i-2<=val2+40) && (oldball_i+2>val2+40))){
											//rimbalza in modo strano solo se colpisce gli angoli 
												indice_i=2;
												indice_j=1;
												if(mossa==4){//se sbatte sul paddle da dx 
												mossa=3;
												}else if(mossa==1){//se sbatte sul paddle da sx
												mossa=2;
												}
											} 	
								if(oldball_j-2==31 || oldball_j-1==31 ){//esce sopra e prende un punto il player1
									score1=score1+1;	
									punto=1;
									mossa=5;
									
								}
			}
			
			if(score2==1){ 
		//		pause=1;
				perso=1;
				LCD_Clear(Black);
				GUI_Text(6, 160, (uint8_t *) str1 , White, Black); //score1
				GUI_TextInverse(232, 176, (uint8_t *) "5" , White, Black); //score2
				GUI_TextInverse(98, 90, (uint8_t *) "niw ouY", White, Black);
				GUI_Text(90, 230, (uint8_t *) "You lose", White, Black);
				GUI_Text(80, 152, (uint8_t *) "Press INT0", White, Black);	
				disable_timer(0);
			}else if(score1==5){ 
		//		pause=1;   //non mi fa fare le cose che sono dentro al timer
				perso=1;  //sono pronta per il int0
			  LCD_Clear(Black);
				GUI_Text(6, 160, (uint8_t *) "5" , White, Black); //score1
				GUI_TextInverse(232, 176, (uint8_t *) str2 , White, Black); //score2
				GUI_TextInverse(98, 90, (uint8_t *) "esol ouY", White, Black);
				GUI_Text(90, 230, (uint8_t *) "You win", White, Black);
				GUI_Text(80, 152, (uint8_t *) "Press INT0", White, Black);
				
				disable_timer(0);
		}
			
		 //}	
			moveball(mossa);
		
} 

  
	
	LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{ 
	if(pause==0){	
	if(val2==6) direzione2=0;
  if(val2==194) direzione2=1;
	if(direzione2==1) val2--;
	else if(direzione2==0) val2++;
	movepaddle2(val2);
	}
	LPC_TIM1->IR = 1;			/* clear interrupt flag */
 
	return;
}



/******************************************************************************
**                            End Of File
******************************************************************************/
