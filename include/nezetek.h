#ifndef NEZETEK_H
#define NEZETEK_H
#include "main.h"
#include "segedfuggvenyek.h"

int elsoNapAHeten(int ev, int honap, int nap);
void Nezetvalaszt(Esemeny esemenyek[], int db);
void napiNezet(Esemeny esemenyek[], int db, int ev, int honap, int nap);
void hetiNezet(Esemeny esemenyek[], int db, int ev, int honap, int nap);
void haviNezet(Esemeny esemenyek[], int db, int ev, int honap);

#endif // NEZETEK_H