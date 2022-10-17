#ifndef _WORDLE_H_
#define _WORDLE_H_
#include "termcodes.h"
#include <string>

struct Wordle {
    std::string code;
    Wordle(std::string code);
    void playGame();
};

#endif
