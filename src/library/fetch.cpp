#include <openssl/evp.h>
#include <fstream>
#include <iostream>
#include <vector>

std::string decrypt(const std::vector<unsigned char>& ciphertext, const std::string& key) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    const EVP_CIPHER *cipher = EVP_aes_256_cbc();

    // Extract IV from the end of the ciphertext
    std::vector<unsigned char> iv(ciphertext.end() - EVP_MAX_IV_LENGTH, ciphertext.end());
    std::vector<unsigned char> actual_ciphertext(ciphertext.begin(), ciphertext.end() - EVP_MAX_IV_LENGTH);

    std::vector<unsigned char> plaintext(actual_ciphertext.size());
    int len;
    EVP_DecryptInit_ex(ctx, cipher, NULL, (unsigned char*)key.c_str(), iv.data());
    EVP_DecryptUpdate(ctx, plaintext.data(), &len, actual_ciphertext.data(), actual_ciphertext.size());
    int plaintext_len = len;
    EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len);
    plaintext_len += len;

    plaintext.resize(plaintext_len);

    EVP_CIPHER_CTX_free(ctx);
    return std::string(plaintext.begin(), plaintext.end());
}
