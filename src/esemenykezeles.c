#include "esemenykezeles.h"
#include "segedfuggvenyek.h"
#include "debugmalloc.h"
#include <stdbool.h>

#include "esemenykezeles.h"
#include "segedfuggvenyek.h"
#include "debugmalloc.h"
#include <stdbool.h>
#include <ctype.h>

// Global events array
extern Esemeny events[MAX_EVENTS];
extern int esemenyCount; // Tracks the number of currently stored events

bool ujEsemeny(Esemeny events[], int *db, int maxItems) {
    char temp[MAX_STRING];
    int ervenyesAdat;

    // Check if there's space in the global array
    if (*db >= maxItems) {
        printf("Hiba: Nincs eleg hely az esemenyek tarolasahoz!\n");
        return false;
    }

    // Reference to the next available slot in the array
    Esemeny *ujEsemeny = &events[*db];

    printf("\nUj esemeny letrehozasa\n");
    printf("========================\n\n");

    // Event name input
    do {
        printf("Esemeny neve: ");
        biztos_gets(temp, MAX_STRING);
        ervenyesAdat = strlen(temp) > 0 && strlen(temp) < MAX_FIELD_LENGTH;
        if (!ervenyesAdat) {
            printf("A nev nem lehet ures és maximum %d karakter hosszu! Kerem, adja meg ujra.\n", MAX_FIELD_LENGTH);
        }
    } while (!ervenyesAdat);
    strncpy(ujEsemeny->nev, temp, MAX_FIELD_LENGTH);

    // Date input
    do {
        printf("Datum (EEEE/HH/NN): ");
        biztos_gets(temp, MAX_STRING);
        ervenyesAdat = sscanf(temp, "%d/%d/%d", 
                              &ujEsemeny->ev, &ujEsemeny->honap, &ujEsemeny->nap) == 3 &&
                       datum_ellenorzes(ujEsemeny->ev, ujEsemeny->honap, ujEsemeny->nap);
        if (!ervenyesAdat) {
            printf("Ervenytelen datum! Kerem, adja meg ujra.\n");
        }
    } while (!ervenyesAdat);

    // Start time input
    do {
        printf("Kezdo idopont (OO:PP): ");
        biztos_gets(temp, MAX_STRING);
        ervenyesAdat = sscanf(temp, "%d:%d", &ujEsemeny->oratol, &ujEsemeny->perctol) == 2 &&
                       ido_ellenorzes(ujEsemeny->oratol, ujEsemeny->perctol);
        if (!ervenyesAdat) {
            printf("Ervenytelen idopont! Kerem, adja meg ujra.\n");
        }
    } while (!ervenyesAdat);

    // End time input
    do {
        printf("Befejezo idopont (OO:PP): ");
        biztos_gets(temp, MAX_STRING);
        ervenyesAdat = sscanf(temp, "%d:%d", &ujEsemeny->oraig, &ujEsemeny->percig) == 2 &&
                       ido_ellenorzes(ujEsemeny->oraig, ujEsemeny->percig) &&
                       (ujEsemeny->oraig > ujEsemeny->oratol || 
                        (ujEsemeny->oraig == ujEsemeny->oratol && 
                         ujEsemeny->percig > ujEsemeny->perctol));
        if (!ervenyesAdat) {
            printf("Ervenytelen idopont vagy a befejezes a kezdés előtt van! Kerem, adja meg ujra.\n");
        }
    } while (!ervenyesAdat);

    // Location input
    printf("Helyszin: ");
    biztos_gets(temp, MAX_STRING);
    strncpy(ujEsemeny->helyszin, temp, MAX_FIELD_LENGTH);

    // Notes input
    printf("Megjegyzes: ");
    biztos_gets(temp, MAX_STRING);
    strncpy(ujEsemeny->megjegyzes, temp, MAX_FIELD_LENGTH);

    // Increment the event count after successfully adding the event
    (*db)++;

    printf("\nAz esemeny sikeresen hozzaadva!\n");
    return true;
}


//Esemény kiírása
void esemeny_kiiras(const Esemeny e) {
    printf("\nEsemeny neve: %s\n", e.nev);
    printf("Datum: %04d/%02d/%02d\n", e.ev, e.honap, e.nap);
    printf("Idopont: %02d:%02d - %02d:%02d\n", e.oratol, e.perctol, e.oraig, e.percig);
    printf("Helyszin: %s\n", e.helyszin);
    printf("Megjegyzes: %s\n", e.megjegyzes);
}


//Esemény törlése
void esemeny_torles(Esemeny events[], int *db) {
    if (*db == 0) {
        printf("Nincs torolheto esemeny!\n");
        return;
    }

    printf("\nValassza ki a torolni kivant esemenyt:\n");
    for (int i = 0; i < *db; i++) {
        printf("%d. ", i + 1);
        esemeny_kiiras(events[i]);
    }

    int valasztas;
    do {
        printf("\nTorlendo esemeny szama (1-%d): ", *db);
        scanf("%d", &valasztas);
        getchar();
    } while (valasztas < 1 || valasztas > *db);

    printf("\nBiztosan torolni szeretne az alabbi esemenyt?\n");
    esemeny_kiiras(events[valasztas - 1]);
    printf("\nIgen (i) / Nem (n): ");

    char valasz;
    scanf("%c", &valasz);
    getchar();

    if (tolower(valasz) == 'i') {
        for (int i = valasztas - 1; i < *db - 1; i++) {
            events[i] = events[i + 1];
        }

        (*db)--;
        printf("Esemeny torolve!\n");
    } else {
        printf("Esemeny torlese megszakitva.\n");
    }
}


void kereses(Esemeny esemenyek[], int db) {
    if (db == 0) {
        printf("Nincs esemeny az adatbazisban!\n");
        return;
    }

    printf("\nKereses tipusa:\n");
    printf("1. Datum szerint\n");
    printf("2. Idopont szerint\n");
    printf("3. Nev szerint\n");
    printf("4. Helyszin szerint\n");
    printf("5. Megjegyzes szerint\n");
    
    int tipus;
    printf("Valasszon keresesi tipust (1-5): ");
    scanf("%d", &tipus);
    getchar();
    
    char keresett[MAX_STRING];
    int ev, honap, nap, ora, perc;
    int talalatok = 0;
    
    switch (tipus) {
        case 1: // Dátum szerinti keresés
            printf("Adja meg a datumot (EEEE/HH/NN): ");
            if (scanf("%d/%d/%d", &ev, &honap, &nap) != 3 || 
                !datum_ellenorzes(ev, honap, nap)) {
                printf("Ervenytelen datum format!\n");
                return;
            }
            getchar();
            
            printf("\nTalalatok:\n");
            for (int i = 0; i < db; i++) {
                if (esemenyek[i].ev == ev && esemenyek[i].honap == honap && esemenyek[i].nap == nap) {
                    esemeny_kiiras(esemenyek[i]);
                    talalatok++;
                }
            }
            break;
            
        case 2: //Időpont szerinti keresés
            printf("Adja meg az idopontot (OO/PP): ");
            if (scanf("%d/%d", &ora, &perc) != 2 || 
                !ido_ellenorzes(ora, perc)) {
                printf("Ervenytelen idopont format!\n");
                return;
            }
            getchar();
            
            printf("\nTalalatok:\n");
            for (int i = 0; i < db; i++) {
                if ((esemenyek[i].oratol <= ora && esemenyek[i].oraig >= ora) ||
                    (esemenyek[i].oratol == ora && esemenyek[i].perctol <= perc) ||
                    (esemenyek[i].oraig == ora && esemenyek[i].percig >= perc)) {
                    esemeny_kiiras(esemenyek[i]);
                    talalatok++;
                }
            }
            break;
            
        case 3: //Név szerinti keresés
            printf("Adja meg a keresett nevet: ");
            biztos_gets(keresett, MAX_STRING);
            
            printf("\nTalalatok:\n");
            for (int i = 0; i < db; i++) {
                if (tartalmazza(esemenyek[i].nev, keresett)) {
                    esemeny_kiiras(esemenyek[i]);
                    talalatok++;
                }
            }
            break;
            
        case 4: //Helyszín szerinti keresés
            printf("Adja meg a keresett helyszint: ");
            biztos_gets(keresett, MAX_STRING);
            
            printf("\nTalalatok:\n");
            for (int i = 0; i < db; i++) {
                if (tartalmazza(esemenyek[i].helyszin, keresett)) {
                    esemeny_kiiras(esemenyek[i]);
                    talalatok++;
                }
            }
            break;
            
        case 5: //Megjegyzés szerinti keresés
            printf("Adja meg a keresett szoveget a megjegyzesben: ");
            biztos_gets(keresett, MAX_STRING);
            
            printf("\nTalalatok:\n");
            for (int i = 0; i < db; i++) {
                if (tartalmazza(esemenyek[i].megjegyzes, keresett)) {
                    esemeny_kiiras(esemenyek[i]);
                    talalatok++;
                }
            }
            break;
            
        default:
            printf("Ervenytelen keresesi tipus!\n");
            return;
    }
    
    if (talalatok == 0) {
        printf("Nem talalhato esemeny a megadott feltetelekkel.\n");
    } else {
        printf("\nOsszesen %d talalat.\n", talalatok);
    }
}

void modositas(Esemeny esemenyek[], int db) {
    if (db == 0) {
        printf("Nincs modosithato esemeny az adatbazisban!\n");
        return;
    }

    printf("\nHogyan szeretne keresni a modositando esemenyre?\n");
    printf("1. Nev szerint\n");
    printf("2. Datum szerint\n");
    printf("3. Idopont szerint\n");
    printf("4. Helyszin szerint\n");
    printf("5. Megjegyzes szerint\n");
    printf("6. Osszes esemény listazasa\n");

    int keresesTipus;
    printf("Valasszon keresési típust (1-6): ");
    scanf("%d", &keresesTipus);
    getchar();

    // Array to store indices of matching events
    int talalatok[MAX_EVENTS];
    int talalatokSzama = 0;

    char keresett[MAX_STRING];

    switch (keresesTipus) {
        case 1: // Név szerinti keresés
            printf("Keresett nev: ");
            biztos_gets(keresett, MAX_STRING);

            for (int i = 0; i < db; i++) {
                if (tartalmazza(esemenyek[i].nev, keresett)) {
                    talalatok[talalatokSzama++] = i;
                }
            }
            break;

        case 2: // Dátum szerinti keresés
            printf("Keresett datum (EEEE/HH/NN): ");
            biztos_gets(keresett, MAX_STRING);

            for (int i = 0; i < db; i++) {
                char datum[20];
                sprintf(datum, "%d/%02d/%02d", 
                        esemenyek[i].ev, 
                        esemenyek[i].honap, 
                        esemenyek[i].nap);
                if (tartalmazza(datum, keresett)) {
                    talalatok[talalatokSzama++] = i;
                }
            }
            break;

        case 3: // Időpont szerinti keresés
            printf("Keresett idopont (OO:PP): ");
            biztos_gets(keresett, MAX_STRING);

            for (int i = 0; i < db; i++) {
                char idopont[20];
                sprintf(idopont, "%02d:%02d - %02d:%02d", 
                        esemenyek[i].oratol, 
                        esemenyek[i].perctol,
                        esemenyek[i].oraig, 
                        esemenyek[i].percig);
                if (tartalmazza(idopont, keresett)) {
                    talalatok[talalatokSzama++] = i;
                }
            }
            break;

        case 4: // Helyszín szerinti keresés
            printf("Keresett helyszin: ");
            biztos_gets(keresett, MAX_STRING);

            for (int i = 0; i < db; i++) {
                if (tartalmazza(esemenyek[i].helyszin, keresett)) {
                    talalatok[talalatokSzama++] = i;
                }
            }
            break;

        case 5: // Megjegyzés szerinti keresés
            printf("Keresett szoveg a megjegyzesben: ");
            biztos_gets(keresett, MAX_STRING);

            for (int i = 0; i < db; i++) {
                if (tartalmazza(esemenyek[i].megjegyzes, keresett)) {
                    talalatok[talalatokSzama++] = i;
                }
            }
            break;

        case 6: // Összes esemény listázása
            for (int i = 0; i < db; i++) {
                talalatok[talalatokSzama++] = i;
            }
            break;

        default:
            printf("Ervenytelen keresesi tipus!\n");
            return;
    }

    if (talalatokSzama == 0) {
        printf("Nem talalhato esemeny a megadott feltetelekkel!\n");
        return;
    }

    // Találatok kilistázása
    printf("\nTalalt esemenyek:\n");
    for (int i = 0; i < talalatokSzama; i++) {
        printf("\n%d. ", i + 1);
        esemeny_kiiras(esemenyek[talalatok[i]]);
    }

    // Esemény kiválasztása
    int valasztottIndex;
    do {
        printf("\nMelyik esemenyt szeretne modositani? (1-%d): ", talalatokSzama);
        scanf("%d", &valasztottIndex);
        getchar();
    } while (valasztottIndex < 1 || valasztottIndex > talalatokSzama);

    // Kiválasztott esemény módosítása
    int modosithatoIndex = talalatok[valasztottIndex - 1];
    esemeny_modositas(&esemenyek[modosithatoIndex]);

    printf("\nA modositasok sikeresen mentve!\n");
}
