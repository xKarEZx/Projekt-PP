#include <stdio.h>
#include "fileio.h"

int saveToFile(Database *db, const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) return 0;

    fwrite(&db->size, sizeof(int), 1, f);
    fwrite(db->data, sizeof(Mech), db->size, f);
    fclose(f);
    return 1;
}

int loadFromFile(Database *db, const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) return 0;

    fread(&db->size, sizeof(int), 1, f);
    db->capacity = db->size + 10;
    db->data = realloc(db->data, sizeof(Mech) * db->capacity);
    fread(db->data, sizeof(Mech), db->size, f);
    fclose(f);
    return 1;
}

