#include "segedfuggvenyek.h"
#include "debugmalloc.h"
#include <stdlib.h>

int datum_ellenorzes(int ev, int honap, int nap) {
    if (ev < 1900 || ev > 2500) return 0;
    if (honap < 1 || honap > 12) return 0;
    
    int napok[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((ev % 4 == 0 && ev % 100 != 0) || (ev % 400 == 0)) napok[1] = 29;
    
    return nap >= 1 && nap <= napok[honap - 1];
}

int ido_ellenorzes(int ora, int perc) {
    return ora >= 0 && ora <= 23 && perc >= 0 && perc <= 59;
}   


char* string_masolat(const char* str) {
    char* uj = (char*)malloc(strlen(str) + 1);
    if (uj) strcpy(uj, str);
    return uj;
}


char* biztos_gets(char* str, int meret) {
    if (fgets(str, meret, stdin)) {
        str[strcspn(str, "\n")] = 0;
        return str;
    }
    return NULL;
}

int esemeny_osszehasonlitas(const void* a, const void* b) {
    const Esemeny* ea = *(const Esemeny**)a;
    const Esemeny* eb = *(const Esemeny**)b;
    
    if (ea->ev != eb->ev) return ea->ev - eb->ev;
    if (ea->honap != eb->honap) return ea->honap - eb->honap;
    if (ea->nap != eb->nap) return ea->nap - eb->nap;
    if (ea->oratol != eb->oratol) return ea->oratol - eb->oratol;
    return ea->perctol - eb->perctol;
}

int tartalmazza(const char* szoveg, const char* keresett) {
    if (!szoveg || !keresett) return 0;
    
    char* szoveg_kisbetu = strdup(szoveg);
    char* keresett_kisbetu = strdup(keresett);
    
    // Minden karakter kisbetűssé alakítása
    for (int i = 0; szoveg_kisbetu[i]; i++) {
        szoveg_kisbetu[i] = tolower(szoveg_kisbetu[i]);
    }
    for (int i = 0; keresett_kisbetu[i]; i++) {
        keresett_kisbetu[i] = tolower(keresett_kisbetu[i]);
    }
    
    int eredmeny = strstr(szoveg_kisbetu, keresett_kisbetu) != NULL;
    
    /*free(szoveg_kisbetu);
    free(keresett_kisbetu);
    */
    return eredmeny;
}

void esemeny_modositas(Esemeny* esemeny) {
    char temp[MAX_STRING];
    int ervenyesAdat;
    int valasztas;
    
    do {
        printf("\nMelyik mezot szeretne modositani?\n");
        printf("1. Nev: %s\n", esemeny->nev);
        printf("2. Datum: %d/%02d/%02d\n", esemeny->ev, esemeny->honap, esemeny->nap);
        printf("3. Kezdo idopont: %02d:%02d\n", esemeny->oratol, esemeny->perctol);
        printf("4. Befejezo idopont: %02d:%02d\n", esemeny->oraig, esemeny->percig);
        printf("5. Helyszin: %s\n", esemeny->helyszin);
        printf("6. Megjegyzes: %s\n", esemeny->megjegyzes);
        printf("0. Modositas befejezese\n");
        printf("\nValasztas: ");
        
        scanf("%d", &valasztas);
        getchar();
        
        switch(valasztas) {
            case 1: //Név módosítása
                do {
                    printf("Uj nev: ");
                    biztos_gets(temp, MAX_STRING);
                    ervenyesAdat = strlen(temp) > 0 && strlen(temp) < MAX_FIELD_LENGTH;
                    if (!ervenyesAdat) {
                        printf("A nev nem lehet ures es maximum %d karakter hosszu! Kerem, adja meg ujra.\n", MAX_FIELD_LENGTH - 1);
                    }
                } while (!ervenyesAdat);

                
                strncpy(esemeny->nev, temp, MAX_FIELD_LENGTH - 1);
                esemeny->nev[MAX_FIELD_LENGTH - 1] = '\0';

                printf("Nev sikeresen modositva!\n");

                break;
                
            case 2: //Dátum módosítása
                do {
                    printf("Uj datum (EEEE/HH/NN): ");
                    biztos_gets(temp, MAX_STRING);

                    int ev, honap, nap;
                    ervenyesAdat = sscanf(temp, "%d/%d/%d", &ev, &honap, &nap) == 3 &&
                                datum_ellenorzes(ev, honap, nap);

                    if (ervenyesAdat) {
                        esemeny->ev = ev;
                        esemeny->honap = honap;
                        esemeny->nap = nap;
                        printf("Datum sikeresen modositva!\n");
                    } else {
                        printf("Ervenytelen datum! Kerem, adja meg ujra a formatumot (EEEE/HH/NN).\n");
                    }
                } while (!ervenyesAdat);

                break;
                
            case 3: //Kezdő időpont módosítása
                do {
                    printf("Uj kezdo idopont (OO:PP): ");
                    biztos_gets(temp, MAX_STRING);
                    int ora, perc;
                    ervenyesAdat = sscanf(temp, "%d:%d", &ora, &perc) == 2 &&
                                  ido_ellenorzes(ora, perc) &&
                                  (ora < esemeny->oraig || 
                                   (ora == esemeny->oraig && perc < esemeny->percig));
                    if (ervenyesAdat) {
                        esemeny->oratol = ora;
                        esemeny->perctol = perc;
                    } else {
                        printf("Ervenytelen idopont vagy kesobb van mint a befejezes! Kerem, adja meg ujra.\n");
                    }
                } while (!ervenyesAdat);
                break;
                
            case 4: //Befejező időpont módosítása
                do {
                    printf("Uj befejezo idopont (OO:PP): ");
                    biztos_gets(temp, MAX_STRING);
                    int ora, perc;
                    ervenyesAdat = sscanf(temp, "%d:%d", &ora, &perc) == 2 &&
                                  ido_ellenorzes(ora, perc) &&
                                  (ora > esemeny->oratol || 
                                    (ora == esemeny->oratol && perc > esemeny->perctol));
                    if (ervenyesAdat) {
                        esemeny->oraig = ora;
                        esemeny->percig = perc;
                    } else {
                        printf("Ervenytelen idopont vagy korabban van mint a kezdes! Kerem, adja meg ujra.\n");
                    }
                } while (!ervenyesAdat);
                break;
                
            case 5: //Helyszín módosítása
                printf("Uj helyszin: ");
                biztos_gets(temp, MAX_STRING);

                if (strlen(temp) < MAX_FIELD_LENGTH) {
                    strncpy(esemeny->helyszin, temp, MAX_FIELD_LENGTH - 1);
                    esemeny->helyszin[MAX_FIELD_LENGTH - 1] = '\0';
                    printf("Helyszin sikeresen modositva!\n");
                } else {
                    printf("Hiba: A helyszin tul hosszu! Maximum %d karakter engedelyezett.\n", MAX_FIELD_LENGTH - 1);
                }
                break;
                
            case 6://Megjegyzés módosítása
                printf("Uj megjegyzes: ");
                biztos_gets(temp, MAX_STRING);
                if (strlen(temp) < MAX_FIELD_LENGTH) {
                    strncpy(esemeny->megjegyzes, temp, MAX_FIELD_LENGTH - 1);
                    esemeny->megjegyzes[MAX_FIELD_LENGTH - 1] = '\0'; // Ensure null-termination
                    printf("Megjegyzes sikeresen modositva!\n");
                } else {
                    printf("Hiba: A megjegyzés tul hosszu! Maximum %d karakter engedelyezett.\n", MAX_FIELD_LENGTH - 1);
                }               
                break;

                
            case 0:
                printf("Modositas befejezve.\n");
                break;
                
            default:
                printf("Ervenytelen valasztas!\n");
        }
        
    } while (valasztas != 0);
}