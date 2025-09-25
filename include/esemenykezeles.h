#ifndef ESEMENYKEZELES_H
#define ESEMENYKEZELES_H
#include "main.h"
#include "segedfuggvenyek.h"
#include "fajlkezeles.h"
#include <stdbool.h>

bool ujEsemeny(Esemeny events[], int *db, int maxItems);
void esemeny_kiiras(const Esemeny e);
void esemeny_torles(Esemeny events[], int *db);
void modositas(Esemeny esemenyek[], int db) ;
void kereses(Esemeny esemenyek[], int db);

#endif // ESEMENYKEZELES_H