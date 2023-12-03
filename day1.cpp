#include <fstream>
#include <string>
#include <iostream>
#include <map>
int main()
{
    std::ifstream inputfile("day1input.txt");
    std::string currentline;
    // also need to consider "written out" digits (part 2)
    std::map<std::string, int> translations;
    translations["one"] = 1;
    translations["two"] = 2;
    translations["three"] = 3;
    translations["four"] = 4;
    translations["five"] = 5;
    translations["six"] = 6;
    translations["seven"] = 7;
    translations["eight"] = 8;
    translations["nine"] = 9;
    int sum = 0;


    // Once input file is out of lines, std::getline will return a "false" from a bool perspective. (EOF flag turns on)
    while(std::getline(inputfile, currentline))
    {

        // now we need to identify the first and last number and add it to sum (they could be the same)
        // examples
        // a line 1abc2 would evaluate to 12
        // a line treb7uchet would evaluate to 77

        // intuition: start from the left of the string, find the first number, break, then start from the right, find the first number, break
        // this potentially saves some time in the average case, which the first num and second num are near the left and right respectively
        // and should still work fine for left and right == same number case
        // since the left digit is in the 10's place, we'll multiply it by ten first before adding it to our sum.

        // left for first num
        // fun fact: C++ ints cannot be null. So there's not really a way to check if it's yet to be assigned. That seems to be more of a pointer thing
        // So for now, we'll assign it to -1 to start, as this is an impossible value for this problem.

        // part 2: include strings!

        std::cout << "\nCurrent line: " << currentline;
        int left = -1;
        for(int i = 0; i < currentline.size(); i++)
        {
            // simple first thing: if we find a digit, we got it
            if(isdigit(currentline[i]))
            {
                left = currentline[i] - '0'; // ASCII conversion
                break;
            }

            // what if it is a number spelled out though? numbers one-nine are 3-5 characters long, so we can check substrings from i to (i + 2/ i + 3/ i + 4)
            // bounds checking, substr does do it for us, but this is probably more efficient to avoid unecessary iterations through the map
            // remember! substr is (index to start from, inclusive), (number of chars!)
            if(currentline.size()- i >= 2)
            {
                std::string sub = currentline.substr(i, 3);
                auto it = translations.find(sub);
                if(it != translations.end())
                {
                    left = it->second;
                    break;
                }
            }
            if(currentline.size() - i >= 3)
            {
                std::string sub = currentline.substr(i, 4);
                auto it = translations.find(sub);
                if(it != translations.end())
                {
                    left = it->second;
                    break;
                }
            }
            if(currentline.size() - i >= 4)
            {
                std::string sub = currentline.substr(i, 5);
                auto it = translations.find(sub);
                if(it != translations.end())
                {
                    left = it->second;
                    break;
                }
            }
        }
        std::cout << "\nLeft: " << left;

        // Do it from the right side now. The most difficult part for me this time was doing the right indexing properly for the "word numbers" (it's simpler then I thought)
        int right = -1;
        for(int i = currentline.size() - 1; i >= 0; i--)
        {
            if(isdigit(currentline[i]))
            {
                right = currentline[i] - '0';
                break;
            }

            // check for spellings of a number
            if(i >= 2)
            {
                std::string sub = currentline.substr(i - 2, 3);
                auto it = translations.find(sub);
                if(it != translations.end())
                {
                    right = it->second;
                    break;
                }
            }
            if(i >= 3)
            {
                std::string sub = currentline.substr(i - 3, 4);
                auto it = translations.find(sub);
                if(it != translations.end())
                {
                    right = it->second;
                    break;
                }
            }
            if(i >= 4)
            {
                std::string sub = currentline.substr(i - 4, 5);
                auto it = translations.find(sub);
                if(it != translations.end())
                {
                    right = it->second;
                    break;
                }
            }
        }
        std::cout << "\nRight: " << right;

        // we could "null checK" or see if our values were instantiated here by seeing if they == -1, but nah. We'll trust the problem (crosses fingers)
        sum += (left * 10) + right;
    }
    // the answer!
    std::cout << "\nAnswer: " << sum << '\n';

    return 0;
}