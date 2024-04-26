#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cstdlib>
#include <ctime>

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
        unsigned long long w[5] = {0};
        int empty_space = 0;
        size_t string_index = 0;
        size_t past_index = 0;
        bool leftOversChecked = false;
        size_t actualStringSize = 0;

        if(k.length() < 28)
        {
          empty_space = 28 - k.length();
        }

        for(size_t i = 0; i < 28; i+=6)
        {
            //size_t indexOfSixLetters = i/6;
            int index = i/6;
            if(empty_space > 6)
            {
              //std::cout << empty_space << " " << index << std::endl;
              w[index] = 0;
              empty_space -= 6;
              //std::cout << empty_space << std::endl;
              continue;
            }
            else if(k.length()%6 == 0 && empty_space > 0)
            {
                w[index] = 0;
                empty_space -= 6;
                continue;
            }
            if(k.length() > 6 && leftOversChecked == false && k.length()%6 != 0)
            {
              string_index = string_index + k.length() % 6;
              actualStringSize = std::min(string_index, k.length());
              leftOversChecked = true;
            }
            else
            {
              string_index += 6;
              actualStringSize = std::min(string_index, k.length());
            }
            
            //std::cout << "string size: " << actualStringSize << std::endl;
            //int num = letterDigitToNumber(c);
            //reverse order
            unsigned long long base = 1;
            //unsigned long long r = base * 36 % rValues[0];
            for(size_t j = actualStringSize; j > past_index; j--)
            {
                w[index] += (base * letterDigitToNumber(k[j-1]));
                std::cout << k[j-1] << " " << letterDigitToNumber(k[j-1]) << " " << w[index] << std::endl;
                base *= 36;
            }
            past_index = string_index;
        }
        
        HASH_INDEX_T hash_value = 0;
        for(size_t i = 0; i < 5; i++)
        {
            hash_value += rValues[i] * w[i];
        }

        return hash_value;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(isdigit(letter))
        {
            HASH_INDEX_T new_letter = letter - '0' + 26;
            return new_letter;
        }
        else
        {
            HASH_INDEX_T new_letter = tolower(letter) - 'a';
            return new_letter;
        }
        return -1;
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
