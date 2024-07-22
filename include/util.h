#ifndef UTIL_H
#define UTIL_H

#include <string>

char fetchNextStep();

int handleNextStep(char nextStep);

std::string parseUserInput();

void handleFile(std::string fileName, std::string key);

#endif // UTIL_H


