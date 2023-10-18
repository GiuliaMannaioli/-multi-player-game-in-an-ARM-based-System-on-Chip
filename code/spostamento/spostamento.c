
#include "../GLCD/GLCD.h" 
#include "../timer/timer.h"

volatile int oldval=0, aggiornato=0, aggiornato2=0, oldval2=0;
volatile int oldball_i=232 , oldball_j=163;
extern int indice_i, indice_j, direzione2;
int zero=0;

void moveball(int mossa){
	switch(mossa){
				case 0: //mi ci va solo la prima volta
					oldball_i = 232-indice_i;
					oldball_j = 163+indice_j;
					LCD_DrawBall(oldball_i, oldball_j, Green);
				break;
				case 1: //alto a dx 
					oldball_i =oldball_i+indice_i;
					oldball_j =oldball_j-indice_j;
					LCD_DrawBall(oldball_i,oldball_j, Green); 
				break;
				case 2:  //in basso a dx
					oldball_i =oldball_i+indice_i;
					oldball_j =oldball_j+indice_j;
					LCD_DrawBall(oldball_i, oldball_j, Green);
				break;
				case 3:  //basso a sx
					oldball_i =oldball_i-indice_i;
					oldball_j =oldball_j+indice_j;
					LCD_DrawBall(oldball_i, oldball_j, Green);
				break;
				case 4: //alto a sx 
					oldball_i =oldball_i-indice_i;
					oldball_j =oldball_j-indice_j; 
					LCD_DrawBall(oldball_i,oldball_j, Green);
				break;
				case 5: //se esce
					oldball_i=232;
					oldball_j=163;
				
//				disable_timer(0);
//				reset_timer(0);
//				enable_timer(0);
					break;
				  default:
					break;
			}
		}
	

void movepaddle( unsigned short val){
int i;
 if(LPC_TIM0-> TCR==1){ //se il timer 1 è attivo
	 
		if(aggiornato==1){
			for(i=0;i<10;i++){  //cancello il vecchio puddle
			LCD_DrawLine(oldval,298-i,oldval+40,298-i, Black);
			}
		aggiornato=0;
		}
	for(i=0;i<10;i++){  //nuovo puddle
		LCD_DrawLine(val,298-i,val+40,298-i, Green);
		oldval = val;
	}
	aggiornato=1;
	
 }
}


void movepaddle2(int val2){
int i;
 if(LPC_TIM0-> TCR==1){ //se il timer 0 è attivo
	
			if(aggiornato2==1){ //cancello il vecchio puddle
				if(direzione2==0){
							for(i=0;i<10;i++){  //cancello a sx
							LCD_DrawLine(oldval2,32-i,oldval2,32-i, Black);
							}
							for(i=0;i<10;i++){  //nuovo paddle
							LCD_DrawLine(val2+40,32-i,val2+40,32-i, Green);
							oldval2 = val2;
						  }
				}else if(direzione2==1){ //devo cancellare al contrario
							for(i=0;i<10;i++){  
							LCD_DrawLine(oldval2+40,32-i,oldval2+40,32-i, Black);
							}
							for(i=0;i<10;i++){  //nuovo paddle
							LCD_DrawLine(val2,32-i,val2,32-i, Green);
							oldval2 = val2;
						  }
				}
			
		}
			
		if (aggiornato2==0){
			for(i=0;i<10;i++){  //primavolta
				LCD_DrawLine(val2,32-i,val2+40,32-i, Green);
				oldval2 = val2;
			}
			aggiornato2=1;
		 }
	 }
		
}



