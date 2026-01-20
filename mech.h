#ifndef MECH_H
#define MECH_H

#define MAX_MODEL 100
#define MAX_KLASA 30
#define MAX_PILOT 50
#define MAX_STAN 30

typedef struct {
    char model[MAX_MODEL];      // identyfikator – niezmienialny
    char klasa[MAX_KLASA];
    int moc_reaktora;            // 0–99
    char pilot[MAX_PILOT];       // opcjonalny
    char stan[MAX_STAN];
} Mech;

#endif
