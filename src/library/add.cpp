#include "../include/library/add.h"
#include "../include/util.h"
#include "../include/json.h"
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <iostream>
#include <fstream>

std::string toHex(const std::vector<unsigned char>& data) {
    // Converts to a readable hex so it can be saved in the .json
    std::ostringstream oss;
    for (unsigned char byte : data) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return oss.str();
}

std::vector<unsigned char> encryptPassword(const std::string& password, const std::vector<unsigned char>& key) {
    std::vector<unsigned char> encryptedPassword(AES_BLOCK_SIZE);
    AES_KEY aesKey;
    AES_set_encrypt_key(key.data(), 128, &aesKey);
    AES_encrypt(reinterpret_cast<const unsigned char*>(password.data()), encryptedPassword.data(), &aesKey);
    return encryptedPassword;
}

void savePassword(const std::string& website, const std::string& password, const std::string& fileName) {
    nlohmann::json jsonData;

    // Read existing data in json object
    std::ifstream inputFile(fileName);
    if (inputFile.is_open()) {
        inputFile >> jsonData;
        inputFile.close();
    } else {
        if (inputFile.fail() && !inputFile.eof()) {
            throw std::runtime_error("Unable to open file for reading existing data.");
        }
    }
    
    jsonData["passwords"][website] = password;

    std::ofstream outputFile(fileName, std::ios::trunc);
    if (outputFile.is_open()) {
        outputFile << jsonData.dump(4);
        outputFile.close();
    } else {
        throw std::runtime_error("Unable to open the file to write new data to.");
    }
}

void addPassword(std::string website, const std::string& password, const std::string& fileName) {
    // Apply a transform to lowercase the website
    std::transform(website.begin(), website.end(), website.begin(), ::tolower);

    std::vector<unsigned char> key = fetchKey(fileName);
    std::vector<unsigned char> encryptedPassword = encryptPassword(password, key);
    std::string encryptedPassword_str = toHex(encryptedPassword);
    savePassword(website, encryptedPassword_str, fileName);
}
