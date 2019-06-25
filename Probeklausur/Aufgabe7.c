#include "aufgaben extern.h"
#include <stdio.h>
#include <stdint.h>

#include "TI_Lib.h"
#include "tft.h"

int8_t stateSE(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr);
int8_t stateS0(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr);
int8_t stateS1(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr);
int8_t stateS2(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr);
int8_t stateS3(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr);
int8_t stateS4(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr);
int8_t stateS5(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr);
int8_t stateS6(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr);
int8_t (*State[])(int8_t,int8_t, int8_t*, int8_t*)= {stateSE,stateS0,stateS1,stateS2,stateS3,stateS4,stateS5,stateS6};


int8_t STATEPOINTER = 0;
static int setS7(uint8_t* S7ptr);


int inittimer();

int aufgabe7(){
	printf("\n\n\n\n\n\n\n-------------------------------------------\n");
	uint8_t BK_K[]={1,3,7,6,4,5,77};
	uint8_t BK_F[] = {1,10,9,2,3,5,2,3};
	uint8_t S7Wert;
	int8_t QS = 0; //akkumulation
	int8_t Y = 0; //counter
	int i = 0;
	inittimer();
	while(1){
	
		while( (TIM2->SR & TIM_SR_UIF) ==0){
			//WAIT WHILE UIF != 1
		}
		TIM2->SR = ~TIM_SR_UIF; //RESET FLAG
		//DO:
		//DEBUGPOLLING:
		while((0x01 << 6) != (GPIOE->IDR & (0x01<<6))){
			i=0; //reset bk index, fange von vorne an
		}
		//readinputs
		//READPHASE
		setS7(&S7Wert);
		uint8_t s7 = S7Wert;
		uint8_t pointer = STATEPOINTER;
		uint8_t bkwert =  BK_K[i];
	
		//Arbeitsphase

		State[pointer]( bkwert,s7, &QS, &Y);
		printf("BK index: %d\n",i);
		printf("STATE: S%d\n", STATEPOINTER-1);
		printf("QS: %d\n",QS);
		printf("Y: %d\n\n",Y);
		i++;
		i=i%7;

	}


}

int inittimer(){
	//INIT TIMER
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //ENABLE TIMER 
	TIM2->CR1 = 0;
	TIM2->CR2 = 0;
	TIM2->PSC = 4-1; //PSC SO EINGESTELLT, DAS ES ca alle 0,05 mikrosekunden läuft
	TIM2->ARR = 42000000-1;
	TIM2->CR1 = TIM_CR1_CEN | TIM_CR1_ARPE;
	
	
}


static int setS7(uint8_t* S7ptr){
	*S7ptr = (0x01 << 7) != (GPIOE->IDR & (0x01<<7));
}


int8_t stateSE(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr){
	*Yptr = 0;
	*qsPtr = 0;
	if(S7 == 0){	
		return 0;
	}
	STATEPOINTER++;
	return 0;
}

int8_t stateS0(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr){
	
	if(S7 == 1 | BK != 1){	
		*Yptr = 0;
		*qsPtr = 0;
		return 0;
	}
	STATEPOINTER++;
	*Yptr = 0;
	*qsPtr = 1;
	return 0;
}

int8_t stateS1(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr){
	if(S7 == 1){	
		*Yptr = 0;
		*qsPtr = 0;
		STATEPOINTER = 0;

		return 0;
	}
	switch(BK){
	
		case 1:
			*Yptr = 0;
			*qsPtr += BK;
			break;
		
		case 3:
			*Yptr = 0;
			*qsPtr += BK;
			STATEPOINTER++;
			break;
		default:
			*Yptr = 0;
			*qsPtr = 0;
			STATEPOINTER = 0;
			
			break;
	}
}

int8_t stateS2(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr){

	if(S7 == 1){	
		*Yptr = 0;
		*qsPtr = 0;
		STATEPOINTER = 0;
		
		return 0;
	}
	switch(BK){
	
		case 1:
			*Yptr = 0;
			*qsPtr = 1;
			STATEPOINTER = 1+1;
			break;
		
		case 7:
			*Yptr = 0;
			*qsPtr += BK;
			STATEPOINTER++;
			break;
		default:
			*Yptr = 0;
			*qsPtr = 0;
			STATEPOINTER = 0;
			
			break;
	}	
	return 0;
}
	
int8_t stateS3(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr){

	if(S7 == 1){	
		*Yptr = 0;
		*qsPtr = 0;
		STATEPOINTER = 0;
		
		return 0;
	}
	switch(BK){
	
		case 1:
			*Yptr = 0;
			*qsPtr = 1;
			STATEPOINTER = 1+1;
			break;
		
		case 6:
			*Yptr = 0;
			*qsPtr += BK;
			STATEPOINTER++;
			break;
		
		default:
			*Yptr = 0;
			*qsPtr = 0;
			STATEPOINTER = 0;

			break;
	}
	return 0;
}

int8_t stateS4(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr){
	
	if(S7 == 1){	
		*Yptr = 0;
		*qsPtr = 0;
		STATEPOINTER = 0;

		return 0;
	}
	switch(BK){
	
		case 1:
			*Yptr = 0;
			*qsPtr = 1;
			STATEPOINTER = 1+1;
			break;
		
		case 4:
			*Yptr = 0;
			*qsPtr += BK;
			STATEPOINTER++;
			break;
		
		default:
			*Yptr = 0;
			*qsPtr = 0;
			STATEPOINTER = 0;

			break;
	}
	return 0;
}


int8_t stateS5(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr){

	if(S7 == 1){	
		*Yptr = 0;
		*qsPtr = 0;
		STATEPOINTER = 0;

		return 0;
	}
	switch(BK){
	
		case 1:
			*Yptr = 0;
			*qsPtr = 1;
			STATEPOINTER = 1+1;
			break;
		
		case 5:
			*Yptr = 1;
			*qsPtr += BK;
			STATEPOINTER++;
			break;
		
		default:
			*Yptr = 0;
			*qsPtr = 0;
			STATEPOINTER = 0;

			break;
	}
	return 0;
}
	
	
int8_t stateS6(int8_t BK, int8_t S7, int8_t* qsPtr, int8_t* Yptr){

	if(BK==1){
		*Yptr = 0;
		*qsPtr = 1;
		STATEPOINTER = 1+1;
		return 0;
	}
	*Yptr = 0;
	*qsPtr = 0;
	STATEPOINTER = 0+1;
	return 0;
	
}
	
	
	
	
	
	
	
