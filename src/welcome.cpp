#include "welcome.h"
#include <algorithm>
#include <iostream>
#include <cctype>
#include <string>

int welcomeMessage() {
    std::cout << "Welcome to MLock!\n\nWhat would you like to do? ([G]enerate, [L]ibrary)" << std::endl;

    return 0;
}

char fetchNextStep() {
    char c;
    bool validInput = false;
    
    while (!validInput) {
        std::string response;
        std::cin >> response;

        std::transform(response.begin(), response.end(), response.begin(), ::tolower);

        if (response == "generate") {
            c = 'g';
            validInput = true;
        } else if (response == "library") {
            c = 'l';
            validInput = true;
        } else if (response.length() == 1) {
            c = response.front();
            c = tolower(c);

            switch (c) {
                case 'g':
                    validInput = true;
                    break;
                case 'l':
                    validInput = true;
                    break;
                default:
                    std::cout << "Please try again. What would you like to do? ([G]enerate, [L]ibrary)" << std::endl;
            }
        }
    }

    return c;
}
