#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"
#include "fileio.h"

/* MODELE */
const char *MODELS[] = {
    "PT91-Twardy",
    "LeopardA2",
    "Rosomak",
    "Rak",
    "K2-PL"
};
#define MODEL_COUNT 5

/* KLASY */
const char *CLASSES[] = {
    "szturmowy",
    "wsparcia",
    "rozpoznawczy",
    "obronny"
};
#define CLASS_COUNT 4

/* STANY */
const char *STATES[] = {
    "sprawny",
    "uszkodzony",
    "w_naprawie",
    "demontaz"
};
#define STATE_COUNT 4

int readString(char *buf, int size) {
    if (!fgets(buf, size, stdin)) return 0;
    buf[strcspn(buf, "\n")] = '\0';
    return 1;
}

int readInt(int *v) {
    char b[50], *e;
    if (!fgets(b, sizeof(b), stdin)) return 0;
    *v = (int)strtol(b, &e, 10);
    return e != b && (*e == '\n' || *e == '\0');
}

int choose(const char *title, const char **list, int count, char *out) {
    int c;
    printf("\n=== %s ===\n", title);
    for (int i = 0; i < count; i++)
        printf(" %d. %s\n", i + 1, list[i]);
    printf(" 0. Powrot\n");
    printf("Wybor: ");

    if (!readInt(&c) || c < 1 || c > count)
        return 0;

    strcpy(out, list[c - 1]);
    return 1;
}

void menu() {
    printf("\n====================================\n");
    printf("  SYSTEM ZARZADZANIA FLOTA MECHOW\n");
    printf("====================================\n");
    printf(" 1. Dodaj mecha\n");
    printf(" 2. Usun mecha\n");
    printf(" 3. Wyswietl flote\n");
    printf(" 4. Szukaj po klasie\n");
    printf(" 5. Szukaj po mocy\n");
    printf(" 6. Sortuj po modelu\n");
    printf(" 7. Sortuj po mocy\n");
    printf(" 8. Zapisz do pliku\n");
    printf(" 9. Wczytaj z pliku\n");
    printf(" 0. Wyjscie\n");
    printf("====================================\n");
}

int main() {
    Database db;
    initDatabase(&db);

    int c;
    do {
        menu();
        printf("Wybor: ");
        if (!readInt(&c)) continue;

        if (c == 1) {
            Mech m;

            if (!choose("WYBOR MODELU", MODELS, MODEL_COUNT, m.model)) continue;
            if (!choose("WYBOR KLASY", CLASSES, CLASS_COUNT, m.klasa)) continue;

            printf("Moc reaktora (0–999): ");
            if (!readInt(&m.moc_reaktora) ||
                m.moc_reaktora < 0 || m.moc_reaktora > 999)
                continue;

            printf("Pilot (- brak): ");
            readString(m.pilot, sizeof(m.pilot));
            if (strcmp(m.pilot, "-") == 0) m.pilot[0] = '\0';

            if (!choose("STAN TECHNICZNY", STATES, STATE_COUNT, m.stan)) continue;

            addMech(&db, m);
        }

        else if (c == 2) {
            int index;
            listMechs(&db);

            printf("Podaj numer mecha do usuniecia: ");
            if (!readInt(&index)) continue;

            removeMechByIndex(&db, index);
        }

        else if (c == 3) listMechs(&db);
        else if (c == 4) {
            char k[30];
            if (!choose("KLASA", CLASSES, CLASS_COUNT, k)) continue;
            searchByClass(&db, k);
        }
        else if (c == 5) {
            int min;
            printf("Minimalna moc: ");
            if (readInt(&min)) searchByPower(&db, min);
        }
        else if (c == 6) sortByModel(&db);
        else if (c == 7) sortByPower(&db);
        else if (c == 8) {
            char f[100];
            printf("Nazwa pliku do zapisu: ");
            if (readString(f, sizeof(f))) saveToFile(&db, f);
        }
        else if (c == 9) {
            char f[100];
            printf("Nazwa pliku do wczytania: ");
            if (readString(f, sizeof(f))) loadFromFile(&db, f);
        }

    } while (c != 0);

    freeDatabase(&db);
    return 0;
}
