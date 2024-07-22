#ifndef ADD_H
#define ADD_H

#include <vector>
#include <string>

std::vector<unsigned char> generateKey();

std::vector<unsigned char> encryptPassword(std::string password, std::vector<unsigned char> key);

void savePassword(std::string website, std::string password, std::string fileName);

void addPassword(std::string website, std::string password, std::string fileName);

#endif // ADD_H
