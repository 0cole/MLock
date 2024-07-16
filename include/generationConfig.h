#ifndef GENERATION_CONFIG_H
#define GENERATION_CONFIG_H

#include <string>

class GenerationConfig {
public:
    GenerationConfig(int len, bool includeSpecialChars, bool includeCapitalLetters);

    int getLen() const;
    bool isIncludeSpecialChars() const;
    bool isIncludeCapitalLetters() const;

    void setLen(int length);
    void setIncludeSpecialChars(bool includeSpecialChars);
    void setIncludeCapitalLetters(bool includeCapitalLetters);

private:
    int len;
    bool includeSpecialChars;
    bool includeCapitalLetters;
};

#endif // GENERATION_CONFIG_H
