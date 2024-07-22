#include "../include/generate.h"
#include "../include/generationConfig.h"
#include "../include/library/add.h"
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

    std::cout << "Generating a password with a length of " << len << 
        " chars, digits = " << std::boolalpha << includeDigits << 
        ", capital letters = " << std::boolalpha << includeCapital << 
        ", and special chars = " << std::boolalpha << includeSpecial << std::endl;

    // Generate the password
    std::string password;
    std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr))); // Seed = current time
    std::uniform_int_distribution<> distribution(0, charSet.size() - 1);

    for (int i = 0; i < len; i++) {
        password += charSet[distribution(generator)];
    }

    return password;
}

bool getBooleanInput(const std::string& prompt) {
    std::cout << prompt;
    std::string result = parseUserInput();
    if (result == "true" || result == "t") {
        return true;
    } else if (result == "false" || result == "f") {
        return false;
    } else {
        std::cout << "Error: Invalid input; please enter true/false." << std::endl;
        return getBooleanInput(prompt); // Recursive call to prompt again
    }
}

GenerationConfig& editConfig(GenerationConfig& config) {
    bool noexit = true;

    while (noexit) {
        std::string newline = "\n";
        std::cout << "Which criteria would you like to change?" << newline << 
            " - [L]en: " << config.getLen() << newline << 
            " - [D]igits: " << std::boolalpha << config.isIncludeDigits() << newline <<
            " - [C]apitals: " << std::boolalpha << config.isIncludeCapitalLetters() << newline <<
            " - [S]pecial chars: " << std::boolalpha << config.isIncludeSpecialChars() << newline <<
            " - [E]xit" << std::endl;
        std::string input = parseUserInput();

        // Changing length
        if (input == "len" || input == "l") {
            std::cout << "Enter a new length (current length = " << config.getLen() << "): ";
            try {
                int newLen;
                std::cin >> newLen;

                // Make sure the user enters a valid integer > 0
                if (std::cin.fail() || newLen < 1) {
                    throw std::runtime_error("Invalid input; please enter a positive integer.");
                } else {
                    config.setLen(newLen);
                }
            } catch (const std::runtime_error& e ) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        } else if (input == "digits" || input == "d") {
            config.setIncludeDigits(getBooleanInput("Would you like to allow"
                        " digits? [T]rue/[F]alse) "));
        } else if (input == "capitals" || input == "c") {
            config.setIncludeCapitalLetters(getBooleanInput("Would you like to allow"
                        " capital letters? ([T]rue/[F]alse) "));
        } else if (input == "special" || input == "s") {
            config.setIncludeSpecialChars(getBooleanInput("Would you like to allow"
                        " special characters? ([T]rue/[F]alse) "));
        } else if (input == "exit" || input == "e") {
            std::cout << "Returning to the generation interface...\n" << std::endl;
            noexit = false;
        }
    }
    return config;
}

int generationInterface() {
    bool noexit = true;

    // Default config initializaiton
    GenerationConfig config(16, true, true, true);

    while (noexit) {
        std::cout << "What would you like to do?"
            "\n - [G]enerate a password"
            "\n - [C]onfigure the generation settings"
            "\n - [E]xit" << std::endl;
        std::string input = parseUserInput();

        if (input == "generate" || input == "g") {
            std::string password = generate(config);
            std::cout << "Generated Password: " << password
                << ". Would you like to save it? (yes/no) ";

            input = parseUserInput();

            if (input == "yes" || input == "y") {
                std::cout << "Please enter the website you will use this password for: ";
                std::string website = parseUserInput();
                addPassword(website, password, "passwords.json"); // fix the hardcoded filename
            }

        } else if (input == "config" || input == "c") {
            config = editConfig(config); 
        } else if (input == "exit" || input == "e") {
            std::cout << "Returning to the main interface...\n" << std::endl;
            noexit = false;
        }
    }
    return 0;
}
