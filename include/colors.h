#ifndef COLORS_H
#define COLORS_H

namespace colors {
    constexpr char RESET[]   = "\033[0m";
    constexpr char BLACK[]   = "\033[30m";
    constexpr char RED[]     = "\033[31m";
    constexpr char GREEN[]   = "\033[32m";
    constexpr char YELLOW[]  = "\033[33m";
    constexpr char BLUE[]    = "\033[34m";
    constexpr char MAGENTA[] = "\033[35m";
    constexpr char CYAN[]    = "\033[36m";
    constexpr char WHITE[]   = "\033[37m";

    constexpr char BOLDBLACK[]   = "\033[1m\033[30m";
    constexpr char BOLDRED[]     = "\033[1m\033[31m";
    constexpr char BOLDGREEN[]   = "\033[1m\033[32m";
    constexpr char BOLDYELLOW[]  = "\033[1m\033[33m";
    constexpr char BOLDBLUE[]    = "\033[1m\033[34m";
    constexpr char BOLDMAGENTA[] = "\033[1m\033[35m";
    constexpr char BOLDCYAN[]    = "\033[1m\033[36m";
    constexpr char BOLDWHITE[]   = "\033[1m\033[37m";
}

#endif // COLORS_H
