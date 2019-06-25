#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

stringOp(char* s);
static int isUMLAUT(char c);

uint32_t LEcounter = 0;
static int isUMLAUT(char c);

int main(int argc, char **argv){
    char Quellstring[]="Jubel auf alen Aleen bei alen Leuten, die ales erleben wolen";
    stringOp(Quellstring);
    return 0;
}

int stringOp(char* s){
    //stringlänge:
    int size = 0;
    char c = s[size];
    while(c!='\0'){
        size++;
        c = s[size];
        }
    //länge des ziels errechnen
    for(int i  = 0; i < size; i++){
        if(s[i] == 'l'){
            if(i+1<size && i>0){ //speicherzugriffsschutz
                if(s[i+1] == 'e'&& isUMLAUT(s[i-1])){
                    LEcounter++;
                }
            }
        }
    }
    //Create Ziel Array:
    char* Zielstring = malloc(sizeof(char)*(size+LEcounter+1));
    if(Zielstring == NULL){
        return -1;
        }
        
    //zielIndexCounter
    int zIndex = 0;
    
    for(int i = 0; i < size; i++){
        if(s[i] == 'l'){
            if(i+1<size+LEcounter && i>0){ //speicherzugriffsschutz
                if(s[i+1] == 'e'&& isUMLAUT(s[i-1])){
                    Zielstring[zIndex] = 'l';
                    zIndex++;
                    }
                }
            }
        Zielstring[zIndex] = s[i];
        zIndex++;
    }
    Zielstring[size+LEcounter] = '\0';
    printf("%d\n", LEcounter);
    printf("%s\n", Zielstring);
    return 0;
    }
    
static int isUMLAUT(char c){
    return (
    ((c =='a') | (c =='e')) | 
    ((c =='i') | (c =='o')) | 
    ((c =='u') | (c =='A')) | 
    ((c =='E') | (c =='I')) | 
    ((c =='O') | (c =='U'))
    ) ;
}
