#include "../include/util.h"
#include <algorithm>
#include <iostream>
#include <cctype>
#include <string>

char fetchNextStep() {
    char c;
    bool validInput = false;
    
    while (!validInput) {
        std::string response;
        std::cin >> response;

        std::transform(response.begin(), response.end(), response.begin(), ::tolower);

        // Check if the user entered the full word instead of just the first letter
        if (response == "generate") {
            c = 'g';
            validInput = true;
        } else if (response == "library") {
            c = 'l';
            validInput = true;
        } else if (response == "exit") {
            c = 'e';
            validInput = true;
        } else if (response.length() == 1) {
            c = response.front();
            c = tolower(c);
            switch (c) {
                case 'g':
                case 'l':
                case 'e':
                    validInput = true;
                    break;
                default:
                    std::cout << "Please try again. What would you like to do? ([G]enerate, [L]ibrary, [E]xit)" << std::endl;
            }
        }
    }
    return c;
}

int handleNextStep(char nextStep) {
    switch (nextStep) {
        case 'g':
            std::cout << "User chose generate" << std::endl;
            break;
        case 'l':
            std::cout << "User chose library" << std::endl;
            break;
        case 'e':
            std::cout << "Exiting." << std::endl;
            return 2; // Not an error code, but a separate return value to quit the program
        default:
            std::cerr << "Invalid option" << std::endl;
            return 1;
    }
    return 0;
}
