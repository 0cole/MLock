#include "../include/library.h"
#include "../include/util.h"
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

void savePassword(std::string website, std::vector<unsigned char>& vect_password, std::string fileName) {
    std::ofstream file(fileName, std::ios::binary);
    std::string password = reinterpret_cast <const char*>(vect_password.data());
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
        savePassword(website, encryptedPassword, fileName);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int libraryInterface() {
    bool noexit = true;
    std::string fileName = "passwords.txt";
    handleFile(fileName);

    while (noexit) {
        std::cout << "What would you like to do?\n - [A]dd\n - [R]emove\n - [E]xit" << std::endl;
        std::string input = parseUserInput();

        if (input == "add" || input == "a") {
            std::cout << "User chose add." << std::endl;
            addPassword("hello.com", "password123", fileName);
        } else if (input == "remove" || input == "r") {
            std::cout << "User chose remove" << std::endl;
        } else if (input == "exit" || input == "e") {
            std::cout << "Returning to the main interface..." << std::endl;
            noexit = false;
        }
    }
    return 0;
}
