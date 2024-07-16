#ifndef GENERATION_CONFIG_H
#define GENERATION_CONFIG_H

#include <string>

class GenerationConfig {
public:
    GenerationConfig(int len, bool includeDigits, bool includeCapitalLetters, bool includeSpecialChars);

    int getLen() const;
    bool isIncludeDigits() const;
    bool isIncludeCapitalLetters() const;
    bool isIncludeSpecialChars() const;

    void setLen(int length);
    void setIncludeDigits(bool includeDigits); 
    void setIncludeCapitalLetters(bool includeCapitalLetters);
    void setIncludeSpecialChars(bool includeSpecialChars);

private:
    int len;
    bool includeDigits;
    bool includeCapitalLetters;
    bool includeSpecialChars;
};

#endif // GENERATION_CONFIG_H
