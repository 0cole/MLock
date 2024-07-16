#include "../include/generate.h"
#include "../include/generationConfig.h"
#include "../include/util.h"
#include <iostream>
#include <string>

int generationInterface() {
    std::cout << "What would you like to do?\n - [G]enerate - [C]onfigure\n - [E]xit" << std::endl;
    std::string input = parseUserInput();

    if (input == "generate" || input == "g") {
        std::cout << "Generating password" << std::endl;
    }

    return 0;
}
