#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

char fetchNextStep();

int handleNextStep(char nextStep);

std::string parseUserInput();

void handleFile(std::string fileName, std::string key);

std::vector<unsigned char> fetchKey(std::string fileName);

std::vector<unsigned char> stringToVector(const std::string& str);

#endif // UTIL_H


