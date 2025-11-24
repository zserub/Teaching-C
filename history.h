#include <stdlib.h>

#include "calculation.h"

typedef struct {
    Calculation* calculations;
    unsigned int capacity;
    unsigned int count;
} History;

History* createHistory(int initialCapacity) {
    History* history = malloc(sizeof(History));
    if (history == NULL) {
        return NULL;
    }
    history->calculations = malloc(initialCapacity * sizeof(Calculation));
    if (history->calculations == NULL) {
        free(history);
        return NULL;
    }
    history->capacity = initialCapacity;
    history->count = 0;
    return history;
}

void freeHistory(History* history) {
    if (history == NULL) {
        return;
    }
    if (history->calculations != NULL) {
        free(history->calculations);
    }
    free(history);
}

bool addToHistory(History* history, Calculation calc) {
    if (history->count >= history->capacity) {
        unsigned int newCapacity = history->capacity * 2;
        Calculation* newCalcs =
            realloc(history->calculations, newCapacity * sizeof(Calculation));

        if (newCalcs == NULL) {
            printf("Error: Memory allocation failed\n");
            return false;
        }

        history->calculations = newCalcs;
        history->capacity = newCapacity;
    }

    history->calculations[history->count] = calc;
    history->count++;
    return true;
}