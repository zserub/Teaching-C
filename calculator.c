#include <stdbool.h>
#include <stdio.h>

#include "calculation.h"
#include "history.h"
#include "optionHandler.h"

// Gracefully close the program and clear heap memory allocation
void shutdown(History* history) {
    printf("Program exiting...\n");
    fflush(stdout);
    freeHistory(history);
    fprintf(stderr, "Good Bye!");
}

int main() {
    History* history = createHistory(5);
    if (history == NULL) {
        printf("Failed to initialize\n");
        return 1;
    }

    printf(  // Addition; 2. Subtraction; 3. Multiplication; 4. Division
        "============================================\n\tTerminal "
        "Calculator\n============================================\n");
    printf(
        "Choose option:\n1. Perform calculation; 2. View history; 5. Exit\n");

    bool running = true;
    while (running) {
        unsigned int selectedOption = getOption();
        if (selectedOption == 0) continue;
        if (handleOption(history, selectedOption) == progExit) {
            running = false;
        }
    }
    shutdown(history);

    return 0;
}
