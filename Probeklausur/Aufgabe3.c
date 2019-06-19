/*Die Elemente des Byte-Feldes BYTES[] sollen beginnend beim höchsten Element Bit-weise in
die Variable ROM_NO ab dem LSB eingetragen werden. Realisieren Sie zwei geschachtelte
Schleifen, die Bytes und deren Bits zählen. Zeigen Sie mit printf(), dass die Hex-Darstellung
in ROM_NO dann identisch ist zu der in BYTES[].*/
#include <stdint.h>
#include <stdio.h>
int rom_A3();

uint8_t BYTES[8] = {0x4e,0xaa,0xab,0xbc,0xcd,0xde,0xef,0x28};
uint64_t ROM_NO = 0;
uint64_t mask = 0;
uint64_t bitwert = 0;
uint32_t bytecount = 0;
uint32_t bitcount = 0;
uint32_t size = sizeof(BYTES)/sizeof(BYTES[0]);
// mit Bits aus den Bytes füllen

int main(int argc, char **argv)
{
    rom_A3();
	return 0;
}

int rom_A3(){
    
    for(int i = 0; i < size;i++){
        uint8_t temp = BYTES[i];
	//MIT 
        //uint8_t temp = BYTES[size-1-i]; 
        //hat es die selbe reihenfolge wie BYTES[]
        bytecount++;
        for(int y = 0; y < size;y++){
            mask = 0;
            bitwert = 0;
            bitwert = (1<<y & temp);
            mask = bitwert << i*size;
            bitcount++;
            ROM_NO |= mask;
            
        }
        
    }
    printf("0x%lx\n",ROM_NO);
    printf("BYTECOUNT: %d\n",bytecount);
    printf("BITCOUNT: %d\n",bitcount);
    return 0;
    }
    
