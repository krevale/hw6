#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
				unsigned long long w[5] = {0, 0, 0, 0, 0};
				int leng = k.length();
				int ind = 4;
				unsigned long long curr_pow = 1;
				int count = 0;

				for (int i = leng - 1; i>= 0; i--) {
					HASH_INDEX_T hval = letterDigitToNumber(k[i]);
					w[ind] += (hval*curr_pow);
					count++;

					if (count < 6) {
						curr_pow *= 36;
					} else {
						ind--;
						curr_pow = 1;
						count = 0;
					}
				}

				unsigned long long total = 0;

				for (int i = 0; i < 5; i++) {
					total += (rValues[i] * w[i]);
				}

				return total;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				if (letter >= 'A' && letter <= 'Z') {
					letter += 32;
				}
				if (letter >= '0' && letter <= '9') {
					return letter - '0' + 26;
				}

				return letter - 'a';
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
