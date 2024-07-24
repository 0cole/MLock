#include "../include/library/fetch.h"
#include "../include/json.h"
#include "../include/util.h"
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <fstream>
#include <iostream>

std::string fromHex(const std::string& hexStr) {
    // initialize as null ptrs
    std::string result(hexStr.length() / 2, '\0');
    for (size_t i = 0; i < result.size(); ++i) {
        result[i] = static_cast<unsigned char>(std::stoi(hexStr.substr(i * 2, 2), nullptr, 16));
    }
    return result;
}

std::string decrypt(const std::string& data, std::vector<unsigned char> key) {
    std::vector<unsigned char> decrypted(AES_BLOCK_SIZE);
    AES_KEY aesKey;
    AES_set_decrypt_key(key.data(), 128, &aesKey);
    AES_decrypt(reinterpret_cast<const unsigned char*>(data.data()), decrypted.data(), &aesKey);
    return std::string(decrypted.begin(), decrypted.end());
}

std::string fetchPassword(const std::string fileName) {
    std::cout << "Please enter the website you would like to retrieve the password for: ";
    std::string website = parseUserInput();

    if (website.empty()) {
        throw std::runtime_error("Website input is empty.");
    }

    std::vector<unsigned char> encryptionKey = fetchKey(fileName);
    std::string decryptedPassword;
    nlohmann::json jsonData;
    std::ifstream inputFile(fileName);

    if (inputFile.is_open()) {
        try {
            inputFile >> jsonData;
        } catch (const nlohmann::json::parse_error& e) {
            throw std::runtime_error("Error parsing JSON data: " + std::string(e.what()));
        }
        inputFile.close();
    } else {
        if (inputFile.fail() && !inputFile.eof()) {
            throw std::runtime_error("Unable to open file for reading existing data.");
        }
    }

    if (jsonData.contains("passwords") && jsonData["passwords"].is_object()) {
        for (const auto& [key, value] : jsonData["passwords"].items()) {
            if (key == website ) {
                std::string encryptedPassword = fromHex(value);
                decryptedPassword = decrypt(encryptedPassword, encryptionKey);
                std::cout << "Found password for " << website << ": " 
                    << decryptedPassword << std::endl;
                break; // Found the password, skip the rest
            }
        }
    } else {
        throw std::runtime_error("The passwords object is missing."); 
    }

    // If no website in passwords.json matches user input
    if (decryptedPassword.empty()) {
        throw std::runtime_error("No passwords were found for " + website + ". Please try again.");
    }

    return decryptedPassword;
}
