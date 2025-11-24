#include "history.h"

void shutdown(History* history){
    printf("Program exiting...\n");
    freeHistory(history);
    printf("Good Bye!");
}

int	main()
{
    History *history = createHistory(5);
    if (history == NULL) {
        printf("Failed to initialize\n");
        return 1;
    }

    Calculation calc;

    printf("============================================\n\tTerminal Calculator\n============================================\n");
    printf("Perform operation on two number\nOperations:\n1. Addition; 2. Subtraction; 3. Multiplication; 4. Division; 5. Exit\n");
    while(true){
        int calcStatus = performCalc(&calc);
        if(calcStatus == CalcSuccess){
            addToHistory(history, calc);
        }
        else if (calcStatus == CalcExit)
        {
            break;
        }
    }
    shutdown(history);

    return 0;
}
