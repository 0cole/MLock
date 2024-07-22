#include "../include/library/add.h"
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
    std::ofstream file(fileName, std::ios::binary);
    std::string entry = website + password;

    if (file.is_open()) {
        file.write(entry.c_str(), entry.size());
        file.close();
    } else {
        throw std::runtime_error("Unable to open file to write to");
    }
}

void addPassword(std::string website, std::string password, std::string fileName) {
    try {
        std::vector<unsigned char> key = generateKey();
        std::vector<unsigned char> encryptedPassword = encryptPassword(password, key);
        std::string encryptedPassword_str = reinterpret_cast <const char*>(encryptedPassword.data());
        savePassword(website, encryptedPassword_str, fileName);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
