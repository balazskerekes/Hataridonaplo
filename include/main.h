#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_STRING 256
#define FAJLNEV "hataridonaplo.txt"
#define MAX_EVENTS 500
#define MAX_FIELD_LENGTH 80

typedef struct Esemeny {
    char nev[MAX_FIELD_LENGTH];    
    int ev, honap, nap;          
    int oratol, perctol;            
    int oraig, percig;           
    char helyszin[MAX_FIELD_LENGTH]; 
    char megjegyzes[MAX_FIELD_LENGTH];
} Esemeny;

void memoria_felszabaditas();

#endif // MAIN_H
