#ifndef FILEIO_H
#define FILEIO_H

#include "database.h"

int saveToFile(Database *db, const char *filename);
int loadFromFile(Database *db, const char *filename);

#endif

