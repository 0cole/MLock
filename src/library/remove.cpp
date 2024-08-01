#include "../include/library/remove.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

void removePassword(const std::string& website, const std::string& fileName) {
    nlohmann::json jsonData;

    std::ifstream inputFile(fileName);
    if (inputFile.is_open()) {
        inputFile >> jsonData;
        inputFile.close();
    } else {
        throw std::runtime_error("Unable to open file for reading existing data.");
    }

    if (jsonData.contains("passwords") && jsonData["passwords"].contains(website)) {
        jsonData["passwords"].erase(website);
    } else {
        throw std::runtime_error(website + " does not exist in password library");
    }

    std::ofstream outputFile(fileName, std::ios::trunc);
    if (outputFile.is_open()) {
        outputFile << jsonData.dump(4);
        outputFile.close();
    } else {
        throw std::runtime_error("Unable to open the file to write new data to.");
    }

    std::cout << "Successfully deleted " << website << " from the password library\n" << std::endl;
}
