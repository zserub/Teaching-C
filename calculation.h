#include <stdio.h>
#include <stdbool.h>

typedef enum{
    CalcError = 0,
    CalcSuccess = 1,
    CalcExit = 2
}CalcStatus;

typedef enum
{
    enumFirst = 1,
    add = enumFirst,
    sub,
    mul,
    divide,
    ProgramExit,
    enumLast = ProgramExit
} Operation;

typedef struct
{
    float num1;
    float num2;
    unsigned int operation;
    float result;
} Calculation;

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool requestNumber(const char* prompt, float* num)
{
    printf("%s", prompt);
    if (scanf("%f", num) != 1)
    {
        printf("Error: Invalid input! Please enter a valid number.\n");
        clearInputBuffer();
        return false;
    }
    return true;
}

bool requestOperation(const char *prompt, unsigned int *operation)
{
    printf("%s", prompt);
    if (scanf("%u", operation) != 1)
    {
        printf("%s", "Error: Invalid input! Please enter a valid number.\n");
        clearInputBuffer();
        return false;
    }
    if (*operation < enumFirst || *operation > enumLast)
    {
        printf("Error: Number is not between %u and %u\n", enumFirst, enumLast);
        return false;
    }
    return true;
}

int performCalc(Calculation* calc) {

    if(!requestNumber("First Number: ", &calc->num1)) return CalcError;
    if(!requestNumber("Second Number: ", &calc->num2)) return CalcError;
    if(!requestOperation("Choose operation: ", &calc->operation)) return CalcError;

    switch (calc->operation)
    {
    case add: calc->result = calc->num1 + calc->num2;
            printf("%.2f + %.2f = %.2f\n", calc->num1, calc->num2, calc->result); break;
    case sub: calc->result = calc->num1 - calc->num2;
            printf("%.2f - %.2f = %.2f\n", calc->num1, calc->num2, calc->result); break;
    case mul: calc->result = calc->num1 * calc->num2;
            printf("%.2f * %.2f = %.2f\n", calc->num1, calc->num2, calc->result); break;
    case divide: if(calc->num2 == 0) {printf("Error: Division by 0\n"); return CalcError;}
            calc->result = calc->num1 / calc->num2;
            printf("%.2f / %.2f = %.2f\n", calc->num1, calc->num2, calc->result); break;
    case ProgramExit: return CalcExit;
    default:    printf("Error: Invalid operation value: %d\n", calc->operation);
                calc->result = 0; return CalcError;
    }
    return 1;
}
