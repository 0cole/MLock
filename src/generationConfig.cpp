#include "../include/generationConfig.h"

GenerationConfig::GenerationConfig(int len, bool includeDigits, bool includeCapitalLetters, bool includeSpecialChars): 
    len(len),
    includeDigits(includeDigits), 
    includeCapitalLetters(includeCapitalLetters), 
    includeSpecialChars(includeSpecialChars) {}

// Getters
int GenerationConfig::getLen() const {
    return len;
}

bool GenerationConfig::isIncludeDigits() const {
    return includeDigits;
}

bool GenerationConfig::isIncludeCapitalLetters() const {
    return includeCapitalLetters;
}

bool GenerationConfig::isIncludeSpecialChars() const {
    return includeSpecialChars;
}

// Setters

void GenerationConfig::setLen(int len) {
    this->len = len;
}

void GenerationConfig::setIncludeDigits(bool includeDigits) {
    this->includeDigits = includeDigits;
}

void GenerationConfig::setIncludeCapitalLetters(bool includeCapitalLetters) {
    this->includeCapitalLetters = includeCapitalLetters;
}

void GenerationConfig::setIncludeSpecialChars(bool includeSpecialChars) {
    this->includeSpecialChars = includeSpecialChars;
}


