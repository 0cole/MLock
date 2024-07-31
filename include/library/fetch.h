#ifndef FETCH_H
#define FETCH_H

#include <string>
#include <vector>

std::vector<unsigned char> fromHex(const std::string& hexStr);

std::vector<unsigned char> removePadding(const std::vector<unsigned char>& data);

std::string decrypt(const std::string& data, std::vector<unsigned char> key);

std::string fetchPassword(const std::string fileName);

#endif // FETCH_H
