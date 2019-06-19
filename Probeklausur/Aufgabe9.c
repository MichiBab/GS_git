#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//DEFINE----------------------------------------------
uint8_t AddFilter(char * nm, uint8_t ord, int16_t *array);
void PrintFilter();
int testFilter();

#define NewFilter 0;
#define AddedFilter 1;
#define Error -1;
#define M 1

struct Filter {// mit Etiket/Tag zur Wiedererkennung in Struktur
char *Typ;
uint8_t Ordnung;
int16_t *Koef;
struct Filter *next;// Nur Pointer auf Struktur erlaubt, da sonst kein Abschluss
};
//ENDDEFINE----------------------------------------------

int16_t TP1[23] = {};// Hochpass Koeffizienten Anzahl N+1
int16_t HP1[23] = {};// Tiefpass s.o.
int16_t MAV1[1] = {M};// Moving Average, alle Koeffizienten gleich 1/M: Mittelung

struct Filter *filter = NULL;



int main(int argc, char **argv){
    testFilter();
	return 0;
}

int testFilter(){
    AddFilter("Hochpass",1,TP1);
    AddFilter("Tiefpass",2,HP1);
    AddFilter("MovingAverage",3,MAV1);
    PrintFilter();
    return 0;
    }

// Parameter: Typ, Ordnung, Array-Name der Koeffizieten
uint8_t AddFilter(char * nm, uint8_t ord, int16_t *array){
    if(filter == NULL){//CREATE FILTER, da noch keins entstanden ist
        filter = (struct Filter *) malloc(sizeof(struct Filter));
        if(filter==NULL){
            return Error;
        }
        filter->Typ = nm;
        filter->Ordnung = ord;
        filter->Koef = array;
        filter->next = NULL;
        return NewFilter;
    }
    //getFilter Ohne next
    struct Filter *filterPTR = filter;
    while(filterPTR->next != NULL){
        filterPTR = filterPTR->next;
        }
    //now filterPTR auf letztem objekt
    //create new filter
    struct Filter *fil = (struct Filter *) malloc(sizeof(struct Filter));
    if(fil==NULL){
        return Error;
        }
    filterPTR->next = fil;
    fil->Typ = nm;
    fil->Ordnung = ord;
    fil->Koef = array;
    fil->next = NULL;
    return AddedFilter;
    }
    
void PrintFilter(){
    struct Filter *filterPTR = filter;
    while(filterPTR != NULL){
        printf("%s\n",filterPTR->Typ);
        filterPTR = filterPTR->next;
        }
    }
