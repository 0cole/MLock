#include "../include/library/remove.h"
#include "../include/util.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

void removePassword(const std::string& website, const std::string& fileName) {
    nlohmann::json jsonData = readFromJson(fileName);

    if (jsonData.contains("passwords") && jsonData["passwords"].contains(website)) {
        jsonData["passwords"].erase(website);
    } else {
        throw std::runtime_error(website + " does not exist in password library");
    }

    writeToJson(fileName, jsonData); 

    std::cout << "Successfully deleted " << website << " from the password library\n" << std::endl;
}
