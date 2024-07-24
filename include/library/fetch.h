#ifndef FETCH_H
#define FETCH_H

#include <string>
#include <vector>

std::string fromHex(const std::string& hexStr);

std::string decrypt(const std::string& data, std::vector<unsigned char> key);

std::string fetchPassword(std::string fileName);

#endif // FETCH_H
