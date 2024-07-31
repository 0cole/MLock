#ifndef ADD_H
#define ADD_H

#include <vector>
#include <string>

std::string toHex(const std::vector<unsigned char>& data);

std::vector<unsigned char> applyPadding(const std::vector<unsigned char>& data);

std::vector<unsigned char> encryptPassword(const std::string& password, const std::vector<unsigned char>& key);

void savePassword(const std::string& website, const std::string& password, const std::string& fileName);

void addPassword(std::string website, const std::string& password, const std::string& fileName);

#endif // ADD_H
