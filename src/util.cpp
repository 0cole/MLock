#include "../include/library/library.h"
#include "../include/generate.h"
#include "../include/colors.h"
#include <nlohmann/json.hpp>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cctype>

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
    std::cout << "What would you like to do?"
        "\n - [G]enerate"
        "\n - [L]ibrary"
        "\n - [E]xit" << std::endl;

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
                    std::cout << colors::YELLOW << "\nInvalid input. Please try again." << colors::RESET <<
                        "\n - [G]enerate"
                        "\n - [L]ibrary"
                        "\n - [E]xit" << std::endl;
            }
        }
    }
    return c;
}

int handleNextStep(char nextStep, const std::string& fileName) {
    switch (nextStep) {
        case 'g':
            std::cout << "User chose generate\n" << std::endl;
            generationInterface(fileName);
            break;
        case 'l':
            std::cout << "User chose library\n" << std::endl;
            libraryInterface(fileName);
            break;
        case 'e':
            std::cout << "Exiting." << std::endl;
            return 2; // Not an error code, but a separate return value to quit the program
        default:
            std::cerr << colors::YELLOW << "Invalid option. Please try again.\n" << colors::RESET << std::endl;
            return 1;
    }
    return 0;
}

void addPin(nlohmann::json& jsonObj) {
    // Add more checks here later
    std::cout << "Please enter the master pin you would like to save: ";
    const std::string pin = parseUserInput();
    jsonObj["pin"] = pin;
}

void handleFile(std::string fileName, std::string key) {
    std::filesystem::path filePath = fileName;

    std::cout << "Checking if " << fileName << " exists..." << std::endl;

    // If file does not exist, create it
    if (!std::filesystem::exists(filePath)) { 
        std::ofstream file(filePath, std::ios::binary);

        if(!file) {
            std::cerr << colors::RED << "Failed to create file" << colors::RESET << std::endl;;
        }

        // For now, create a json object with the key and passwords, not ideal at all though
        nlohmann::json jsonObj;

        addPin(jsonObj);
        jsonObj["key"] = key;
        jsonObj["passwords"] = {};

        if (file.is_open()) {
            file << jsonObj.dump(4);
            file.close();
            std::cout << colors::GREEN << "Successfully created and wrote key to " << fileName << colors::RESET<< std::endl;
        }
    } else {
        std::cout << colors::GREEN << fileName << " already exists." << colors::RESET << std::endl;
    }
    std::cout << std::endl; // Add extra line at end for asthetic 
}

std::vector<unsigned char> stringToVector(const std::string& str) {
    return std::vector<unsigned char>(str.begin(), str.end());
}

nlohmann::json readFromJson(const std::string& fileName) {
    nlohmann::json jsonData;
    std::filesystem::path filePath = fileName;
    std::ifstream file(filePath);

    if (file.is_open()) {
        try {
            file >> jsonData;
        } catch (const nlohmann::json::parse_error& e) {
            throw std::runtime_error("Error parsing JSON data: " + std::string(e.what()));
        }
        file.close();
    } else {
        throw std::runtime_error("Unable to open file for reading existing data.");
    }
    return jsonData;
}

void writeToJson(const std::string& fileName, const nlohmann::json& jsonData) {
    std::filesystem::path filePath = fileName;
    std::ofstream file(filePath, std::ios::trunc);

    if (file.is_open()) {
        try {
            file << jsonData.dump(4);
        } catch (const nlohmann::json::parse_error& e) {
            throw std::runtime_error("Error parsing JSON data: " + std::string(e.what()));
        }
        file.close();
    } else {
        throw std::runtime_error("Unable to open file for reading existing data.");
    }
}

std::vector<unsigned char> fetchKey(std::string fileName) {
    nlohmann::json jsonObj = readFromJson(fileName);
    std::string key_str = jsonObj["key"];
    std::vector<unsigned char> key = stringToVector(key_str);
    return key;
}

bool pinConfirmation(const std::string& fileName) {
    std::cout << "Please enter the master pin:";
    const std::string pin = parseUserInput();

    nlohmann::json jsonObj = readFromJson(fileName);
    if (jsonObj["pin"] == pin) {
        std::cout << colors::GREEN << "Pin entered successfully" << colors::RESET << std::endl;
        return true;
    }
    return false;
}
