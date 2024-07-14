#include "../include/util.h"
#include <algorithm>
#include <iostream>
#include <cctype>
#include <string>
    
std::string parseUserInput() {
    // Parses the user input, formats it into a string, and applies a transform to lowercase it
    std::string response;
    std::cin >> response;
    std::transform(response.begin(), response.end(), response.begin(), ::tolower);
    return response;
}

char fetchNextStep() {
    char c;
    bool validInput = false;
    std::cout << "What would you like to do?\n - [G]enerate\n - [L]ibrary\n - [E]xit" << std::endl;

    while (!validInput) {
        std::string input = parseUserInput();

        // Check if the user entered the full word instead of just the first letter
        if (input == "generate") {
            c = 'g';
            validInput = true;
        } else if (input == "library") {
            c = 'l';
            validInput = true;
        } else if (input == "exit") {
            c = 'e';
            validInput = true;
        } else if (input.length() == 1) {
            c = input.front();
            c = tolower(c); // just to be sure, lowercase it again
            switch (c) {
                case 'g':
                case 'l':
                case 'e':
                    validInput = true;
                    break;
                default:
                    std::cout << "Please try again. What would you like to do?\n - [G]enerate\n - [L]ibrary\n - [E]xit" << std::endl;
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
