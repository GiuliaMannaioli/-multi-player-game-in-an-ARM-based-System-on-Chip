/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../led/led.h"
#include "../spostamento/spostamento.h"
#include "../GLCD/GLCD.h" 
#include "../timer/timer.h"

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

unsigned short AD_current;
unsigned short AD_last = 0xFF;     /* Last converted value               */
volatile unsigned short val=0;
extern int pause, prima;

void ADC_IRQHandler(void) {
  	int i =0;
	
 AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */
	
	if((pause==0) && (LPC_TIM0-> TCR==1)){
	if(AD_current!=AD_last){
		if(prima==1){
		for(i=0;i<10;i++){  //cancello il vecchio puddle
			LCD_DrawLine(100,298-i,100+40,298-i, Black);
			}
		prima=0;
	}
		val= AD_current*190/0xFFF;	
		if((val-AD_last*190/0xFFF) <= -20 || (val-AD_last*190/0xFFF) >= 20){ 
			if(val<6) val=6;
			if(val>195) val=195;
				movepaddle(val);
				AD_last = AD_current;
			}
	 }	
 }
}


