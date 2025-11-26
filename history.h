#pragma once

#include <stdbool.h>
#include <stdio.h>
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

bool addToHistory(History* history, const Calculation* calc) {
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

    history->calculations[history->count] = *calc;
    history->count++;
    return true;
}

void printHistory(const History* history) {
    if (history == NULL || history->calculations == NULL) {
        printf("History is empty.\n");
        return;
    }

    printf("=== Calculation History ===\n");
    printf("Total calculations: %u\n\n", history->count);

    for (unsigned int i = 0; i < history->count; i++) {
        const Calculation calc = history->calculations[i];
        char operationSymbol;

        switch (calc.operation)
        {
        case add: operationSymbol = '+'; break;
        case sub: operationSymbol = '-'; break;
        case mul: operationSymbol = '*'; break;
        case divide: operationSymbol = '/'; break;
        
        default:
            printf("Error: Unhandled exception, unkown operation\n");
            operationSymbol = '?';
            break;
        }

        printf("%u.) %.2f %c %.2f = %.3f \n", i+1, calc.num1, operationSymbol, calc.num2, calc.result);
    }
}