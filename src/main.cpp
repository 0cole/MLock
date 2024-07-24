#include "../include/welcome.h"
#include "../include/util.h"
#include <iostream>

int main() {
    bool noexit = true;

    welcomeMessage();

    std::string key = "SuperSecretPassword";
    std::string fileName = "passwords.json";
    handleFile(fileName, key);

    while (noexit) {

        char c = fetchNextStep();

        // If the user wants to exit
        if (handleNextStep(c, fileName) == 2) {
            break;
        }
    }

    return 0;
}
