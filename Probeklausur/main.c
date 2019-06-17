/**
  ******************************************************************************
  * @file    	main.c 
  * @author  	Alfred Lohmann
  *        	  HAW-Hamburg
  *          	Labor für technische Informatik
  *          	Berliner Tor  7
  *          	D-20099 Hamburg
  * @version V1.0
  * @date    23.05.2013
  * @brief   Main program body
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "TI_Lib.h"
#include "tft.h"

//--- For GPIOs -----------------------------
//Include instead of "stm32f4xx.h" for
//compatibility between Simulation and Board
//#include "TI_memory_map.h"

//--- For Touch Keypad ----------------------
//#include "keypad.h"

//--- For Timer -----------------------------
//#include "timer.h"

/**
  * @brief  Main program
  * @param  None
  */
	int aufgabe5();
	
int main(void)
{
	
	
  Init_TI_Board();
  
	aufgabe5();
	
	
  return 0;

}

int aufgabe5(){
	//INIT WERTE
	float werte[480];
	for(int i = 0; i<240;i++){
		werte[i] = 400 * (float)i*1/48000 -1;
	}
	for(int i = 0; i<240; i++){
		werte[i+240] = -400 * (float)i/48000 +1;
	}
	//UPSCALE die werte, da DAC bis 4400 läuft und nur positive werte annimmt
	for(int i = 0; i<480;i++){
		werte[i] = (werte[i]+1) *2000;
	}
	
	//INIT TIMER
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //ENABLE TIMER 
	TIM2->CR1 = 0;
	TIM2->CR2 = 0;
	TIM2->PSC = 4-1; //PSC SO EINGESTELLT, DAS ES ca alle 0,05 mikrosekunden läuft
	TIM2->ARR = 438-1;
	TIM2->CR1 = TIM_CR1_CEN | TIM_CR1_ARPE;
	
	//INIT DAC
	RCC->APB1ENR |= RCC_APB1ENR_DACEN; //ENABLE DAC
	DAC->CR |=1;
	int count = 0;
	//programm
	while(1){
	
		while( (TIM2->SR & TIM_SR_UIF) ==0){
			//WAIT WHILE UIF != 1
		}
		TIM2->SR = ~TIM_SR_UIF; //RESET FLAG
		//DO:
		if(count >= 480){
			count = 0;
		}
		//DAC REGISTER 12 BIT WERTE DIE RIGHT ALIGNED SIND => LINKE 4 BIT SIND IM 16 BIT REGISTER RESERVED
		DAC->DHR12R1 = werte[count];
		count++;
	}
	

}



// EOF
