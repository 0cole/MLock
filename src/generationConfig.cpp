#include "../include/GenerationConfig.h"

GenerationConfig::GenerationConfig(int len, bool includeSpecialChars, bool IncludeCapitalLetters): len(len), includeSpecialChars(includeSpecialChars), includeCapitalLetters(includeCapitalLetters) {}

// Getters
int GenerationConfig::getLen() const {
    return len;
}

bool PasswordConfig::isIncludeSpecialChars() const {
    return includeSpecialChars;
}

bool PasswordConfig::isIncludeCapitalLetters() const {
    return includeCapitalLetters;
}

// Setters

void GenerationConfig::setLen(int len) {
    this->len = len;
}

void GenerationConfig::setIncludeSpecialChars(bool includeSpecialChars) {
    this->includeSpecialChars = includeSpecialChars;
}

void GenerationConfig::setIncludeCapitalLetters(bool includeCapitalLetters) {
    this->includeCapitalLetters = includeCapitalLetters;
}
