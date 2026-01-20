#ifndef DATABASE_H
#define DATABASE_H

#include "mech.h"

typedef struct {
    Mech *data;
    int size;
    int capacity;
} Database;

void initDatabase(Database *db);
void freeDatabase(Database *db);

int addMech(Database *db, Mech m);

/* NOWA FUNKCJA */
int removeMechByIndex(Database *db, int index);

void listMechs(Database *db);
void searchByClass(Database *db, const char *klasa);
void searchByPower(Database *db, int minPower);

void sortByModel(Database *db);
void sortByPower(Database *db);

#endif
