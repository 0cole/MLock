#include <iostream>
#include "../include/util.h"
#include "../include/welcome.h"

int main() {

    welcomeMessage();

    while (true) {

        char c = fetchNextStep();

        // If the user wants to exit
        if (handleNextStep(c) == 2) {
            break;
        }
    }

    return 0;
}
