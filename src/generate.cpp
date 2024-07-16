#include "../include/generate.h"
#include "../include/generationConfig.h"
#include "../include/util.h"
#include <iostream>
#include <string>
#include <random>
#include <ctime>

std::string generate(GenerationConfig& config) {
    // Get config data
    int len = config.getLen();
    bool includeDigits = config.isIncludeDigits();
    bool includeCapital = config.isIncludeCapitalLetters();
    bool includeSpecial = config.isIncludeSpecialChars();

    // Define possibile chars
    std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    std::string capital = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string digit = "0123456789";
    std::string special = "!@#$%^&*()-_=+[]{}|;:,.<>?";

    // Create char set
    std::string charSet = lowercase;
    if (includeDigits) charSet += digit;
    if (includeCapital) charSet += capital;
    if (includeSpecial) charSet += special;

    std::cout << "Generating a password with a length of " << len 
        << " chars, special chars = " << std::boolalpha << includeSpecial 
        << ", digits = " << std::boolalpha << includeDigits
        << ", and capital letters = " << std::boolalpha << includeCapital << std::endl;

    // Generate the password
    std::string password;
    std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr))); // Seed = current time
    std::uniform_int_distribution<> distribution(0, charSet.size() - 1);

    for (int i = 0; i < len; i++) {
        password += charSet[distribution(generator)];
    }

    return password;
}

int generationInterface() {
    std::cout << "What would you like to do?\n - [G]enerate\n - [C]onfigure\n - [E]xit" << std::endl;
    std::string input = parseUserInput();

    GenerationConfig config(16, true, true, true);

    if (input == "generate" || input == "g") {
        std::string password = generate(config);
        std::cout << "Generated Password: " << password << std::endl;
    }

    return 0;
}
