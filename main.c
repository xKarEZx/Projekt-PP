#include <stdio.h>
#include <string.h>
#include "database.h"
#include "fileio.h"

void menu() {
    printf("\n1. Dodaj mecha");
    printf("\n2. Usun mecha");
    printf("\n3. Lista mechow");
    printf("\n4. Szukaj po klasie");
    printf("\n5. Szukaj po mocy");
    printf("\n6. Sortuj po modelu");
    printf("\n7. Sortuj po mocy");
    printf("\n8. Zapisz do pliku");
    printf("\n9. Wczytaj z pliku");
    printf("\n0. Wyjscie\n");
}

int main(int argc, char *argv[]) {
    Database db;
    initDatabase(&db);

    int choice;
    do {
        menu();
        scanf("%d", &choice);

        if (choice == 1) {
            Mech m;
            printf("Model: "); scanf("%s", m.model);
            printf("Klasa: "); scanf("%s", m.klasa);
            printf("Moc reaktora: "); scanf("%d", &m.moc_reaktora);
            printf("Pilot (lub -): "); scanf("%s", m.pilot);
            if (strcmp(m.pilot, "-") == 0) m.pilot[0] = '\0';
            printf("Stan (sprawny/uszkodzony/w_naprawie/demontaz): ");
            scanf("%s", m.stan);

            if (!addMech(&db, m))
                printf("Mech juz istnieje!\n");
        }

        else if (choice == 2) {
            char model[100];
            printf("Model do usuniecia: ");
            scanf("%s", model);
            if (!removeMech(&db, model))
                printf("Nie usunieto mecha.\n");
        }

        else if (choice == 3) listMechs(&db);
        else if (choice == 4) {
            char p[30];
            printf("Prefix klasy: ");
            scanf("%s", p);
            searchByClass(&db, p);
        }
        else if (choice == 5) {
            int m;
            printf("Minimalna moc: ");
            scanf("%d", &m);
            searchByPower(&db, m);
        }
        else if (choice == 6) sortByModel(&db);
        else if (choice == 7) sortByPower(&db);
        else if (choice == 8 && argc > 1) saveToFile(&db, argv[1]);
        else if (choice == 9 && argc > 1) loadFromFile(&db, argv[1]);

    } while (choice != 0);

    freeDatabase(&db);
    return 0;
}
