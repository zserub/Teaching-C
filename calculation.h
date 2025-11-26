#pragma once

#include <stdio.h>
#include <stdbool.h>

//* Forward declaration to avoid circular dependency
void clearInputBuffer();

typedef enum {
    CalcError = 0,
    CalcSuccess = 1,
    CalcExit = 2
} CalcStatus;

typedef enum {
    enumFirst = 1,
    add = enumFirst,
    sub,
    mul,
    divide,
    enumLast = divide
} Operation;

typedef struct {
    float num1;
    float num2;
    unsigned int operation;
    float result;
} Calculation;

bool requestNumber(const char* prompt, float* num) {
    printf("%s", prompt);
    if (scanf("%f", num) != 1) {
        printf("Error: Invalid input! Please enter a valid number.\n");
        clearInputBuffer();
        return false;
    }
    return true;
}

bool requestOperation(const char *prompt, unsigned int *operation) {
    printf("%s", prompt);
    if (scanf("%u", operation) != 1) {
        printf("%s", "Error: Invalid input! Please enter a valid number.\n");
        clearInputBuffer();
        return false;
    }
    if (*operation < enumFirst || *operation > enumLast) {
        printf("Error: Number is not between %u and %u\n", enumFirst, enumLast);
        return false;
    }
    return true;
}

int performCalc(Calculation* calc) {

    if(!requestNumber("First Number: ", &calc->num1)) return CalcError;
    if(!requestNumber("Second Number: ", &calc->num2)) return CalcError;
    if(!requestOperation("Choose operation:\n 1. + ; 2. - ; 3. * ; 4. /\n", 
        &calc->operation)) return CalcError;

    printf("---------------------------\n");

    calc->result = 0;

    switch (calc->operation) {
    case add: calc->result = calc->num1 + calc->num2;
            printf("%.2f + %.2f = %.2f\n", calc->num1, calc->num2, calc->result); break;

    case sub: calc->result = calc->num1 - calc->num2;
            printf("%.2f - %.2f = %.2f\n", calc->num1, calc->num2, calc->result); break;

    case mul: calc->result = calc->num1 * calc->num2;
            printf("%.2f * %.2f = %.2f\n", calc->num1, calc->num2, calc->result); break;

    case divide: if(calc->num2 == 0) {printf("Error: Division by 0\n"); return CalcError;}
            calc->result = calc->num1 / calc->num2;
            printf("%.2f / %.2f = %.2f\n", calc->num1, calc->num2, calc->result); break;

    default:    printf("Error: Invalid operation value: %d\n", calc->operation);
                return CalcError;
    }
    printf("---------------------------\n");
    return CalcSuccess;
}
