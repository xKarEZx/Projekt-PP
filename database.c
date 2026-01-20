#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

void initDatabase(Database *db) {
    db->size = 0;
    db->capacity = 10;
    db->data = malloc(sizeof(Mech) * db->capacity);
}

void freeDatabase(Database *db) {
    free(db->data);
}

static void ensureCapacity(Database *db) {
    if (db->size >= db->capacity) {
        db->capacity *= 2;
        db->data = realloc(db->data, sizeof(Mech) * db->capacity);
    }
}

/* =========================
   DODAWANIE – BEZ BLOKADY
   ========================= */
int addMech(Database *db, Mech m) {
    ensureCapacity(db);
    db->data[db->size++] = m;
    return 1;
}

/* =========================
   USUWANIE PO INDEKSIE
   tylko gdy stan = demontaz
   ========================= */
int removeMechByIndex(Database *db, int index) {
    if (index < 0 || index >= db->size) {
        printf("Nieprawidlowy numer mecha.\n");
        return 0;
    }

    if (strcmp(db->data[index].stan, "demontaz") != 0) {
        printf("Nie mozna usunac – stan != demontaz\n");
        return 0;
    }

    db->data[index] = db->data[--db->size];
    return 1;
}

/* =========================
   LISTA MECHOW Z NUMERAMI
   ========================= */
void listMechs(Database *db) {
    printf("\n--- LISTA MECHOW ---\n");

    if (db->size == 0) {
        printf("(brak mechow w bazie)\n");
        return;
    }

    for (int i = 0; i < db->size; i++) {
        Mech *m = &db->data[i];
        printf("[%d] %s | %s | %d | Pilot: %s | Stan: %s\n",
               i,
               m->model,
               m->klasa,
               m->moc_reaktora,
               strlen(m->pilot) ? m->pilot : "brak",
               m->stan);
    }
}

/* =========================
   WYSZUKIWANIE
   ========================= */
void searchByClass(Database *db, const char *klasa) {
    for (int i = 0; i < db->size; i++)
        if (strcmp(db->data[i].klasa, klasa) == 0)
            printf("%s\n", db->data[i].model);
}

void searchByPower(Database *db, int minPower) {
    for (int i = 0; i < db->size; i++)
        if (db->data[i].moc_reaktora >= minPower)
            printf("%s (%d)\n",
                   db->data[i].model,
                   db->data[i].moc_reaktora);
}

/* =========================
   SORTOWANIE
   ========================= */
static int cmpModel(const void *a, const void *b) {
    return strcmp(((Mech*)a)->model, ((Mech*)b)->model);
}

static int cmpPower(const void *a, const void *b) {
    return ((Mech*)a)->moc_reaktora - ((Mech*)b)->moc_reaktora;
}

void sortByModel(Database *db) {
    qsort(db->data, db->size, sizeof(Mech), cmpModel);
}

void sortByPower(Database *db) {
    qsort(db->data, db->size, sizeof(Mech), cmpPower);
}
