#ifndef HASH_H
#define HASH_H

#include <chrono>
#include <cmath>
#include <iostream>
#include <random>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5]{983132572, 1468777056, 552714139, 984953261,
                            261934300};
    MyStringHash(bool debug = true) {
        if (debug == false) {
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string &k) const {
        int k_l = k.length();
        HASH_INDEX_T w[5];

        bool isBegin = false;
        int startI = k_l - 1;
        for (int i = 4; i >= 0; i--) {
            if (isBegin) {
                w[i] = 0;
                continue;
            }
            HASH_INDEX_T sum = 0;
            HASH_INDEX_T acc = 1;
            for (int i = 0; i < 6; i++) {
                if (startI - i < 0) {
                    isBegin = true;
                    break;
                }
                sum += letterDigitToNumber(tolower(k[startI - i])) * acc;
                acc *= 36;
            }
            startI -= 6;
            w[i] = sum;
        }
        HASH_INDEX_T hash = 0;
        for (int i = 0; i < 5; i++) {
            hash += rValues[i] * w[i];
        }
        return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const {
        if (letter >= 'a' && letter <= 'z') {
            return letter - 97;
        } else if (letter >= '0' && letter <= '9') {
            return letter - 48 + 26;
        } else {
            exit(1);
        }
    }

    // Code to generate the random R values
    void generateRValues() {
        // obtain a seed from the system clock:
        unsigned seed =
            std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(
            seed); // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random
        // number
        for (int i{0}; i < 5; ++i) {
            rValues[i] = generator();
        }
    }
};

#endif
