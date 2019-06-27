#include <stdint.h>
#include "aufgaben extern.h"
#include <math.h>
#include <stdlib.h>
#define N 15
#define M 16
#define frequenz 300 //100 oder 500 oder 1000
//BEI 100: fast das selbe wie sinus, kaum gedämpft; 
//500: eine kurve dann genullt; 1000: auch genullt; bei 300 leicht gedämpft
#define arraysize (8000/frequenz)

uint8_t n = 0; //array index
uint8_t timerinit2(); 
uint8_t arrayinit(float *sinus); //füllt sinus
float sinusDACready[arraysize]; //für dac geupscaled

uint8_t ARRAYFLAG = 0; //ARRAYFLAG, damit main die werte errechnet
uint8_t functionY(float wert); //die mittlerungsfunktion
float* bufferedArray; //buffer array
uint8_t bufferedPointer = 0; //bis 16
float erg = 0; //zur ausgabe; entspricht y(n)
float sinus[arraysize]; //sinus array

uint8_t aufgabe8(){
	arrayinit(sinus);
	
	for(int i = 0; i<arraysize;i++){ //Upgescaled
		sinusDACready[i] = (sinus[i]+1) * 2047; //damit dac bis 4095 läuft(12 bit) 
		//und +1 damit positiv. MAX sinus ist 1; +1 => 2 => 2*2047 =4094
	}
	
	timerinit2();

	//CONFIG
	bufferedArray = (float*) malloc(sizeof(float)*16);
	if(bufferedArray == NULL){
		return -1;
	}
	
	while(1){
	//loop for the interrupts
		if(ARRAYFLAG){ //warte bis interrupt freigibt
		
			functionY(sinus[n]);		
			ARRAYFLAG=0;
			
		}		
	}
}

uint8_t functionY(float wert){
	erg = 0;
	
	for(int i = 0; i<M;i++){
	
		erg+=bufferedArray[i];
		
	}
	erg = (erg / M)+1;
	erg = (erg) * 2047;
}

uint8_t arrayinit(float *sinus){

	for(int i = 0; i<arraysize;i++){
		sinus[i] = sin((2*3.141592654)*(float)i/arraysize) ;
	}
	
}

uint8_t timerinit2(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->CR1 = 0;
	TIM2->CR2 = 0;
	TIM2->PSC = 21-1;
	TIM2->ARR = 500-1;
	TIM2->DIER=TIM_DIER_UIE;
	TIM2->CR1 = TIM_CR1_CEN | TIM_CR1_ARPE;
	NVIC_EnableIRQ(TIM2_IRQn);
	
	//ENABLE DAC1
	RCC->APB1ENR |=RCC_APB1ENR_DACEN;
	DAC->CR |= DAC_CR_EN1;
	//DAC2
	DAC->CR |= DAC_CR_EN2;
}

void TIM2_IRQHandler(){
	bufferedArray[bufferedPointer] = sinus[n];
	TIM2->SR = ~TIM_SR_UIF; //reset flag
	DAC->DHR12R1 = sinusDACready[n];
	DAC->DHR12R2 = erg;
	n++;
	n= n%arraysize;
	bufferedPointer++;
	bufferedPointer = bufferedPointer%M;
	ARRAYFLAG=1; //freigabe für main, damit sie arbeiten darf
}
