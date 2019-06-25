#include "aufgaben extern.h"
#include <stdint.h>
#include <stdio.h>
uint8_t BYTES[8] = {0x4e,0xaa,0xab,0xbc,0xcd,0xde,0xef,0x28};
uint8_t CRCwert = 0; 
uint8_t CRCMASK = 0x50;  //0101 0000

int crcCheck(uint8_t wert);

int aufgabe4(){

	for(int i = 0; i<7;i++){	
		crcCheck(BYTES[7-i]);
	}
	
	return 0;
}

int crcCheck(uint8_t wert){

	for(int i = 0; i<8; i++){
		//get bit
		uint8_t temp = (0x01 << i) & wert;
		uint8_t bitwert = temp>>i;
		//if first crc bit XOR mit temp true ist
		if( ((0x01 & CRCwert) ^ bitwert) == 1){
			CRCwert = CRCwert ^ CRCMASK;
			CRCwert = CRCwert>>1;
			if((0x01 & CRCwert)==1){ //WENN rechts eine 1 stand, nach dem schieben links sie wieder ranfügen
				CRCwert = CRCwert | 0x80;// am MSB vom statusregister wird 1 hinzugefuegt, weil 0x80 --> 1000 0000 ist
			}
		}
		else{
			CRCwert = CRCwert>>1;
		}
	}
	

	return 0;
}
