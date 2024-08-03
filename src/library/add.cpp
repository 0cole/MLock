#include "../include/library/add.h"
#include "../include/util.h"
#include <nlohmann/json.hpp>
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

std::vector<unsigned char> applyPadding(const std::vector<unsigned char>& data) {
    size_t padSize = AES_BLOCK_SIZE - (data.size() % AES_BLOCK_SIZE);
    std::vector<unsigned char> paddedData = data;
    paddedData.insert(paddedData.end(), padSize, static_cast<unsigned char>(padSize));
    return paddedData;
}

std::vector<unsigned char> encryptPassword(const std::string& password, const std::vector<unsigned char>& key) {
    // We ned to apply padding because the data needs to 
    // be a multiple of the AES_BLOCK_SIZE which is 16 bytes
    std::vector<unsigned char> passwordData(password.begin(), password.end());
    std::vector<unsigned char> paddedPassword = applyPadding(passwordData);

    std::vector<unsigned char> encryptedPassword(paddedPassword.size());
    AES_KEY aesKey;
    AES_set_encrypt_key(key.data(), 128, &aesKey);

    for (size_t i = 0; i < paddedPassword.size(); i += AES_BLOCK_SIZE) {
        AES_encrypt(paddedPassword.data() + i, encryptedPassword.data() + i, &aesKey);
    }
    
    return encryptedPassword;
}

void savePassword(const std::string& website, const std::string& password, const std::string& fileName) {
    nlohmann::json jsonData = readFromJson(fileName);
    
    jsonData["passwords"][website] = password;

    writeToJson(fileName, jsonData); 
}

void addPassword(std::string website, const std::string& password, const std::string& fileName) {
    // Apply a transform to lowercase the website
    std::transform(website.begin(), website.end(), website.begin(), ::tolower);

    std::vector<unsigned char> key = fetchKey(fileName);
    std::vector<unsigned char> encryptedPassword = encryptPassword(password, key);
    std::string encryptedPassword_str = toHex(encryptedPassword);
    savePassword(website, encryptedPassword_str, fileName);
}
