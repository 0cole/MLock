#include "../include/library/library.h"
#include "../include/library/fetch.h"
#include "../include/library/add.h"
#include "../include/util.h"
#include <iostream>
#include <fstream>

void handleAddPassword(const std::string& fileName) {
    std::cout << "Please enter the website you would like to save the password for: ";
    std::string website = parseUserInput();
    std::cout << "Please enter the password you would like to save for " << website << ": ";
    std::string password = parseUserInput();

    if (website.empty() || password.empty()) {
        throw std::runtime_error("Website or password is empty. Please try again.");
    }

    addPassword(website, password, fileName);
}

int libraryInterface(const std::string& fileName) {
    bool noexit = true;

    while (noexit) {
        std::cout << "What would you like to do?"
            "\n - [A]dd"
            "\n - [F]etch"
            "\n - [R]emove"
            "\n - [E]xit" << std::endl;

        std::string input = parseUserInput();

        try {
            if (input == "add" || input == "a") {
                std::cout << "User chose add" << std::endl;
                handleAddPassword(fileName);
            } else if (input == "fetch" || input == "f") {
                std::cout << "User chose fetch" << std::endl;
                fetchPassword(fileName);
            } else if (input == "remove" || input == "r") {
                std::cout << "User chose remove" << std::endl;
            } else if (input == "exit" || input == "e") {
                std::cout << "Returning to the main interface..." << std::endl;
                noexit = false;
            }
        } catch (const std::runtime_error& e ) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}
