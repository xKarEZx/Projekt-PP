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

int addMech(Database *db, Mech m) {
    if (findByModel(db, m.model)) {
        return 0; // duplikat
    }
    ensureCapacity(db);
    db->data[db->size++] = m;
    return 1;
}

Mech* findByModel(Database *db, const char *model) {
    for (int i = 0; i < db->size; i++) {
        if (strcmp(db->data[i].model, model) == 0)
            return &db->data[i];
    }
    return NULL;
}

int removeMech(Database *db, const char *model) {
    for (int i = 0; i < db->size; i++) {
        if (strcmp(db->data[i].model, model) == 0) {
            if (strcmp(db->data[i].stan, "demontaz") != 0) {
                printf("Nie mozna usunac – mech nie jest w stanie demontazu!\n");
                return 0;
            }
            db->data[i] = db->data[--db->size];
            return 1;
        }
    }
    return 0;
}

void listMechs(Database *db) {
    for (int i = 0; i < db->size; i++) {
        Mech *m = &db->data[i];
        printf("%s | %s | %d MW | Pilot: %s | Stan: %s\n",
               m->model, m->klasa, m->moc_reaktora,
               strlen(m->pilot) ? m->pilot : "brak",
               m->stan);
    }
}

void searchByClass(Database *db, const char *prefix) {
    for (int i = 0; i < db->size; i++) {
        if (strncmp(db->data[i].klasa, prefix, strlen(prefix)) == 0) {
            printf("%s (%s)\n", db->data[i].model, db->data[i].klasa);
        }
    }
}

void searchByPower(Database *db, int minPower) {
    for (int i = 0; i < db->size; i++) {
        if (db->data[i].moc_reaktora >= minPower) {
            printf("%s (%d MW)\n", db->data[i].model, db->data[i].moc_reaktora);
        }
    }
}

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

