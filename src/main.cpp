#include <iostream>
#include "../include/util.h"
#include "../include/welcome.h"

int main() {

    welcomeMessage();

    char c = fetchNextStep();

    handleNextStep(c);

    return 0;
}
