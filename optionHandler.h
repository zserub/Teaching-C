#pragma once

#include <stdio.h>

#include "calculation.h"
#include "history.h"

typedef enum { calculate = 1, showHistory, progError, progExit } Options;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

unsigned int getOption() {
    printf(
        "Choose option:\n%d. Perform calculation; %d. View history; %d. Exit\n", calculate, showHistory, progExit);
    unsigned int num;
    if (scanf("%u", &num) != 1) {
        printf("Error: Invalid input! Please enter a valid number.\n");
        clearInputBuffer();
        return 0;
    }
    return num;
}

int handleOption(History* history, const int option) {
    switch (option) {
        case calculate:
            Calculation calc;
            int calcStatus = performCalc(&calc);
            if (calcStatus == CalcSuccess) {
                addToHistory(history, &calc);
            }
            break;

        case showHistory:
            printHistory(history);
            break;

        case progExit:
            return progExit;

        default:
            printf("Error: option is incorrect\n");
            return progError;
    }
    return 0;  //! <- Don't do this, magic number
}