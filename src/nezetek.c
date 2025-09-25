#include "nezetek.h"
#include "esemenykezeles.h"
#include "debugmalloc.h"


void napiNezet(Esemeny esemenyek[], int db, int ev, int honap, int nap) {
    int talalatok = 0;
    printf("\nNapi nezet (%04d/%02d/%02d):\n", ev, honap, nap);
    printf("============================\n");

    for (int i = 0; i < db; i++) {
        if (esemenyek[i].ev == ev && esemenyek[i].honap == honap && esemenyek[i].nap == nap) {
            esemeny_kiiras(esemenyek[i]);
            talalatok++;
        }
    }

    if (talalatok == 0) {
        printf("Nincs esemeny ezen a napon.\n");
    } else {
        printf("\nOsszesen %d esemeny talalhato.\n", talalatok);
    }
}

int elsoNapAHeten(int ev, int honap, int nap) {
    struct tm tm = {0};
    tm.tm_year = ev - 1900;
    tm.tm_mon = honap - 1;
    tm.tm_mday = nap;
    mktime(&tm);
    int elsoNap = tm.tm_wday == 0 ? 7 : tm.tm_wday;
    return nap - elsoNap + 1;
}

void hetiNezet(Esemeny esemenyek[], int db, int ev, int honap, int nap) {
    int elsoNap = elsoNapAHeten(ev, honap, nap);
    printf("\nHeti nezet (%04d/%02d/%02d - %04d/%02d/%02d):\n", 
           ev, honap, elsoNap, ev, honap, elsoNap + 6);
    printf("==========================================\n");

    int talalatok = 0;
    char napok[7][15] = {"Hetfo", "Kedd", "Szerda", "Csutortok", "Pentek", "Szombat", "Vasarnap"};
    
    for (int i = 0; i < 7; i++) {
        int aktualisNap = elsoNap + i;
        int aktEv = ev, aktHonap = honap;
        
        //Hónap beállítása
        while (aktualisNap > 31) {
            aktualisNap -= 31;
            aktHonap++;
            if (aktHonap > 12) {
                aktHonap = 1;
                aktEv++;
            }
        }
        
        printf("\n%s (%04d/%02d/%02d):\n", napok[i], aktEv, aktHonap, aktualisNap);
        printf("-----------------------\n");
        
        int napiTalalat = 0;
        for (int j = 0; j < db; j++) {
            if (esemenyek[j].ev == aktEv && 
                esemenyek[j].honap == aktHonap && 
                esemenyek[j].nap == aktualisNap) {
                esemeny_kiiras(esemenyek[j]);
                talalatok++;
                napiTalalat++;
            }
        }
        
        if (napiTalalat == 0) {
            printf("Nincs esemeny ezen a napon.\n");
        }
    }

    printf("\nOsszesen %d esemeny talalhato a heten.\n", talalatok);
}


void haviNezet(Esemeny esemenyek[], int db, int ev, int honap) {
    int talalatok = 0;
    printf("\nHavi nezet (%04d/%02d):\n", ev, honap);
    printf("=====================\n");

    //Hónapok napszáma
    int napok_szama[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    //Szökőév beállítása
    if ((ev % 4 == 0 && ev % 100 != 0) || (ev % 400 == 0)) {
        napok_szama[1] = 29;
    }

    
    for (int nap = 1; nap <= napok_szama[honap - 1]; nap++) {
        int napiTalalat = 0;

        
        for (int i = 0; i < db; i++) {
            if (esemenyek[i].ev == ev && 
                esemenyek[i].honap == honap && 
                esemenyek[i].nap == nap) {
                if (napiTalalat == 0) {
                    printf("\n%04d/%02d/%02d:\n", ev, honap, nap);
                    printf("-------------\n");
                }
                esemeny_kiiras(esemenyek[i]);
                talalatok++;
                napiTalalat++;
            }
        }
    }

    
    if (talalatok == 0) {
        printf("Nincs esemeny ebben a honapban.\n");
    } else {
        printf("\nOsszesen %d esemeny talalhato a honapban.\n", talalatok);
    }
}


void Nezetvalaszt(Esemeny esemenyek[], int db) {
    if (db == 0) {
        printf("Nincs megjelenitendo esemény az adatbázisban!\n");
        return;
    }

    int valasztas;
    char datumStr[MAX_STRING];
    int ev, honap, nap;

    printf("\nValassz nezetet:\n");
    printf("1. Napi nezet\n");
    printf("2. Heti nezet\n");
    printf("3. Havi nezet\n");
    printf("Valasztas: ");
    scanf("%d", &valasztas);
    getchar();

    switch (valasztas) {
        case 1:
            do {
                printf("Kerem, adja meg a datumot (EEEE/HH/NN): ");
                biztos_gets(datumStr, MAX_STRING);
            } while (sscanf(datumStr, "%d/%d/%d", &ev, &honap, &nap) != 3 || 
                     !datum_ellenorzes(ev, honap, nap));
            napiNezet(esemenyek, db, ev, honap, nap);
            break;

        case 2:
            do {
                printf("Kerem, adja meg a het egy napjat (EEEE/HH/NN): ");
                biztos_gets(datumStr, MAX_STRING);
            } while (sscanf(datumStr, "%d/%d/%d", &ev, &honap, &nap) != 3 || 
                     !datum_ellenorzes(ev, honap, nap));
            hetiNezet(esemenyek, db, ev, honap, nap);
            break;

        case 3:
            do {
                printf("Kerem, adja meg az evet es honapot (EEEE/HH): ");
                biztos_gets(datumStr, MAX_STRING);
            } while (sscanf(datumStr, "%d/%d", &ev, &honap) != 2 || 
                     ev < 1900 || ev > 2500 || honap < 1 || honap > 12);
            haviNezet(esemenyek, db, ev, honap);
            break;

        default:
            printf("Ervenytelen valasztas! Kerlek, valassz 1, 2 vagy 3 kozul.\n");
            break;
    }
}
