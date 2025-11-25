#pragma once

#include <stdio.h>

#include "calculation.h"
#include "history.h"

typedef enum { calculate, showHistory, progExit } Options;

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

unsigned int getOption() {
    unsigned int num;
    if (scanf("%u", &num) != 1) {
        printf("Error: Invalid input! Please enter a valid number.\n");
        clearInputBuffer();
        return 0;
    }
    return num;
}

int handleOption(History* history, int option) {
    switch (option) {
        case calculate:
            Calculation calc;
            int calcStatus = performCalc(&calc);
            if (calcStatus == CalcSuccess) {
                addToHistory(history, &calc);
            }
            break;

        case showHistory:

            break;
        case progExit:
            return progExit;

        default:
            printf("Error: option is incorrect\n");
            return 0;
    }
}