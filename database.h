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
int removeMech(Database *db, const char *model);
Mech* findByModel(Database *db, const char *model);

void listMechs(Database *db);

void searchByClass(Database *db, const char *prefix);
void searchByPower(Database *db, int minPower);

void sortByModel(Database *db);
void sortByPower(Database *db);

#endif

