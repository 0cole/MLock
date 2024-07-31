#include "../include/library/fetch.h"
#include "../include/json.h"
#include "../include/util.h"
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <fstream>
#include <iostream>

std::vector<unsigned char> fromHex(const std::string& hexStr) {
    std::vector<unsigned char> result(hexStr.length() / 2);
    for (size_t i = 0; i < result.size(); ++i) {
        result[i] = static_cast<unsigned char>(std::stoi(hexStr.substr(i * 2, 2), nullptr, 16));
    }
    return result;
}

std::vector<unsigned char> removePadding(const std::vector<unsigned char>& data) {
    if (data.empty()) {
        throw std::runtime_error("Data is empty.");
    }

    unsigned char padSize = data.back();

    if (padSize == 0 || padSize > AES_BLOCK_SIZE) {
        throw std::runtime_error("Invalid padding size.");
    } else if (padSize > data.size()) {
        throw std::runtime_error("Padding size is larger than data size.");
    }

    // Return the data without the padding
    return std::vector<unsigned char>(data.begin(), data.end() - padSize);
}

std::string decrypt(const std::string& data, std::vector<unsigned char> key) {
    std::vector<unsigned char> encryptedData = fromHex(data);
    std::vector<unsigned char> decrypted(encryptedData.size());
    AES_KEY aesKey;
    AES_set_decrypt_key(key.data(), 128, &aesKey);

    // Decrypt the data in blocks
    for (size_t i = 0; i < encryptedData.size(); i += AES_BLOCK_SIZE) {
        AES_decrypt(encryptedData.data() + i, decrypted.data() + i, &aesKey);
    }

    std::vector<unsigned char> decryptedData = removePadding(decrypted);

    return std::string(decryptedData.begin(), decryptedData.end());
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
                decryptedPassword = decrypt(value, encryptionKey);
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
