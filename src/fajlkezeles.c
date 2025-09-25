// fajlkezeles.c
#include "fajlkezeles.h"

int esemenyek_betoltese(Esemeny events[], int max_events) {
    FILE* file = fopen(FAJLNEV, "r");
    if (!file) {
        printf("Nem sikerult megnyitni a fajlt.\n");
        return 0;
    }

    int db = 0;
    while (db < max_events && fscanf(file, 
        "%79s %d %d %d %d %d %d %d %79s %79s",
        events[db].nev,
        &events[db].ev, &events[db].honap, &events[db].nap,
        &events[db].oratol, &events[db].perctol,
        &events[db].oraig, &events[db].percig,
        events[db].helyszin,
        events[db].megjegyzes) == 10) {
        db++;
    }

    fclose(file);
    return db;
}

void esemenyek_mentese(Esemeny events[], int db) {
    FILE* file = fopen(FAJLNEV, "w");
    if (!file) {
        printf("Nem sikerult megnyitni a fajlt irasra.\n");
        return;
    }

    for (int i = 0; i < db; i++) {
        fprintf(file, "%s %d %d %d %d %d %d %d %s %s\n",
            events[i].nev,
            events[i].ev, events[i].honap, events[i].nap,
            events[i].oratol, events[i].perctol,
            events[i].oraig, events[i].percig,
            events[i].helyszin,
            events[i].megjegyzes);
    }

    fclose(file);
}
