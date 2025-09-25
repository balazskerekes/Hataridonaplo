#include "main.h"
#include "debugmalloc.h"
#include "esemenykezeles.h"
#include "fajlkezeles.h"
#include "menukezeles.h"
#include "nezetek.h"
#include "segedfuggvenyek.h"
#include <conio.h>
#include <stdbool.h>

// Global events array
Esemeny events[MAX_EVENTS];

void memoria_felszabaditas() {}

int main() {
    int valasztas;
    int db = 0; //Esemenyek szama

    
    db = esemenyek_betoltese(events, MAX_EVENTS);

    do {
        menu_megjelenites();
        printf("\nValasztas: ");
        scanf("%d", &valasztas);
        getchar();

        switch (valasztas) {
            case 1: 
                if (!ujEsemeny(events, &db, MAX_EVENTS)) {
                    printf("Nem sikerult hozzaadni az uj esemenyt.");
                }
                break;

            case 2:
                modositas(events, db);
                esemenyek_mentese(events, db);
                break;

            case 3:
                esemeny_torles(events, &db);
                break;

            case 4:
                kereses(events, db);
                break;

            case 5: 
                if (db == 0) {
                    printf("Nincs megjelenitendo esemeny!\n");
                } else {
                    Nezetvalaszt(events, db);
                }
                break;

            case 6:
                printf("Kilepes...\n");
                break;

            default:
                printf("Ervenytelen valasztas! Kerem, valasszon 1-6 kozott.\n");
        }

        printf("\nNyomjon meg egy billentyut a folytatashoz...");
        getch();

    } while (valasztas != 6);

    memoria_felszabaditas();

    return 0;
}
