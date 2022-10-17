#include <iostream>
#include <string>
#include "wordle.h"
#include "termcodes.h"

using namespace std;

Wordle::Wordle(string code) : code{code} {}

bool checkGuess(string secret, string guess, int len) { 
    char colour[len];
    for (int i = 0; i < len; ++i) {
      colour[i] = '?';
    }
    bool flags[len];
    for (int i = 0; i < len; ++i) {
      flags[i] = false;
    }
    // checking for exact matches
    for (int i = 0; i < len; ++i) {
        if (guess[i] == secret[i]) {
        colour[i] = 'G';
        flags[i] = true;
        }
    }
    // checking for yellow letters
    for (int i = 0; i < len; ++i) {
        if (colour[i] == '?') {
            for (int j = 0; j < len; ++j) {
                if (guess[i] == secret[j] && !flags[j]) {
                    // a match at another location that hasn't been used
                    colour[i] = 'Y';
                    flags[j] = true;
                    break; // end loop so we don't get multiple colours from same letter
                }
            }
        }
    }
    // print out guess with designated colours
    int count = 0;
    for (int i = 0; i < len; ++i) {
      if (colour[i] == 'G') {
        cout << GREEN << guess[i] << RESET;
        ++count;
      } else if (colour[i] == 'Y') {
        cout << YELLOW << guess[i] << RESET;
      } else {
        cout << guess[i];
      }
    }
    if (count == len) return true;
    return false;
}

void Wordle::playGame() {
    string secret = code;
    int secret_len = secret.length();
    string guess;
    int len;
    int count = 0;
    bool ismatch = true;
    cout << "Enter " << secret_len << " length word as guess: ";
    // iterates up to 6 guesses
    while (cin >> guess) {
      len = guess.length();
      // check if incorrect guess size
      if (len != secret_len) {
        cout << "Incorrect guess size, please enter guess of length " << secret_len << ": ";
      // otherwise check guess
      } else {
          ismatch = checkGuess(secret, guess, len);
          cout << "\n";
          ++count;
          if (ismatch) {
            cout << "Congrats you found the word!" << endl;
            return;
          } else if (count == 6) {
              cout << "Out of guesses! The word was: " << secret << endl;
              return;
          } else {
              cout << "Enter " << secret_len << " length word as guess: ";
          }
          ismatch = true;
      }
    } 
      cout << "Out of guesses! The word was: " << secret << endl;
}
