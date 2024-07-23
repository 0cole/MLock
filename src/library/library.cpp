#include "../include/library/library.h"
#include "../include/library/add.h"
#include "../include/util.h"
#include <iostream>
#include <fstream>

int libraryInterface() {
    bool noexit = true;
    std::string fileName = "passwords.json";

    while (noexit) {
        std::cout << "What would you like to do?\n - [A]dd\n - [R]emove\n - [E]xit" << std::endl;
        std::string input = parseUserInput();

        if (input == "add" || input == "a") {
            std::cout << "User chose add." << std::endl;
            addPassword("hello.com", "password123", fileName);
        } else if (input == "remove" || input == "r") {
            std::cout << "User chose remove" << std::endl;
        } else if (input == "exit" || input == "e") {
            std::cout << "Returning to the main interface..." << std::endl;
            noexit = false;
        }
    }
    return 0;
}
