#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

char fetchNextStep();

int handleNextStep(char nextStep, const std::string& fileName);

std::string parseUserInput();

void handleFile(std::string fileName, std::string key);

std::vector<unsigned char> fetchKey(std::string fileName);

std::vector<unsigned char> stringToVector(const std::string& str);

nlohmann::json readFromJson(const std::string& fileName);

#endif // UTIL_H


