#ifndef SEGEDFUGGVENYEK_H
#define SEGEDFUGGVENYEK_H
#include "main.h"

int datum_ellenorzes(int ev, int honap, int nap);
int ido_ellenorzes(int ora, int perc);
char* string_masolat(const char* str);
char* biztos_gets(char* str, int meret);
int esemeny_osszehasonlitas(const void* a, const void* b);
int tartalmazza(const char* szoveg, const char* keresett);
void esemeny_modositas(Esemeny* esemeny);   

#endif //SEGEDFUGGVENYEK_H