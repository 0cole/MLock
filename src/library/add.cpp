#include "../include/library/add.h"
#include "../include/json.h"
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <iostream>
#include <fstream>
#include <string>

std::vector<unsigned char> generateKey() {
    std::vector<unsigned char> key(AES_BLOCK_SIZE);
    if (!RAND_bytes(key.data(), AES_BLOCK_SIZE)) {
        throw std::runtime_error("Error generating random bytes for key");
    }
    return key;
}

std::vector<unsigned char> encryptPassword(std::string password, std::vector<unsigned char> key) {
    std::vector<unsigned char> encryptedPassword(AES_BLOCK_SIZE);
    AES_KEY aesKey;
    AES_set_encrypt_key(key.data(), 128, &aesKey);
    AES_encrypt(reinterpret_cast<const unsigned char*>(password.data()), encryptedPassword.data(), &aesKey);
    return encryptedPassword;
}

void savePassword(std::string website, std::string password, std::string fileName) {
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

void addPassword(std::string website, std::string password, std::string fileName) {
    try {
        std::vector<unsigned char> key = generateKey();
        // std::vector<unsigned char> encryptedPassword = encryptPassword(password, key);
        // std::string encryptedPassword_str = reinterpret_cast <const char*>(encryptedPassword.data());
        savePassword(website, password, fileName);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
