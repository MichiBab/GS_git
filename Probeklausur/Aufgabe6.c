//AUFGABE 6 ----------------------------------------------------------------------


int aufgabe6(){
	//init timer 2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //enable timer
	TIM2->CR1 = 0;
	TIM2->CR2 = 0;
	TIM2->PSC = 4-1;
	TIM2->ARR = 210-1;
	TIM2->DIER = TIM_DIER_UIE; //enable interrupt
	TIM2->CR1 |= TIM_CR1_CEN; //start timer
	TIM2->CR1 |= TIM_CR1_ARPE; //start Interrupt
	
	//Interrupteinstellungen
	NVIC_SetPriorityGrouping(5);
	NVIC_SetPriority(TIM2_IRQn,4); //Priority; umso kleiner umso höher
	NVIC_EnableIRQ(TIM2_IRQn); //Enable timerInterrupt
	
	
	
	//init timer 8
	RCC->APB2ENR |= RCC_APB2ENR_TIM8EN; //enable timer
	TIM8->CR1 = 0;
	TIM8->CR2 = 0;
	TIM8->PSC = 1-1;
	TIM8->ARR = 200-1;
	TIM8->DIER = TIM_DIER_UIE; //enable interrupt
	
	//interrupteinstellungen
	NVIC_SetPriority(TIM8_UP_TIM13_IRQn,3); //Priority 3 damit höher als tim2; umso kleiner umso höher
	NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn); //Enable timerInterrupt
}

void TIM8_UP_TIM13_IRQHandler(){

	TIM8->CR1 = 0; //Stoppt timer 8
	TIM8->SR = ~TIM_SR_UIF; //Reset Flag
	GPIOG->BSRRH = (0x01 << 2); //2 für PIN 2, Deaktiviert pin 2
	
}

void TIM2_IRQHandler(){

	//start tim8
	
	TIM8->CR1 |= TIM_CR1_CEN; //start timer 8
	TIM8->CR1 |= TIM_CR1_ARPE; //start Interrupt
	
	TIM2->SR = ~TIM_SR_UIF; //Reset flag
	
	GPIOG->BSRRL = (0x01 << 2); //macht pin 2 an
	
}

	
	//EOF AUFGABE 6 ----------------------------------------------------------------------
