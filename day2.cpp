#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <limits>
#include <regex>

std::vector<std::string> tokenize_to_vector(std::string input, std::string delims)
{
    std::vector<std::string> result;
    size_t start = 0;
    // "end" is initialized to the index of the first delim
    size_t end = input.find_first_of(delims, start);

    while (end != std::string::npos) {
        if (end != start) {
            result.push_back(input.substr(start, end - start));
        }
        // start now moves over to the end
        start = end + 1;
        end = input.find_first_of(delims, start);
    }

    if (start < input.length()) {
        result.push_back(input.substr(start));
    }

    return result;
}

int main()
{
    int sum = 0;
    int game = 1;


    // read file line by line
    std::ifstream inputfile("day2input.txt");
    std::string currentline;
    std::string my_delims = ":;,";
    while(std::getline(inputfile, currentline))
    {
        // current "game" represented by series of strings
        std::vector<std::string> current_game = tokenize_to_vector(currentline, my_delims);
        for(std::string token : current_game)
        {   
            std::cout << token << '|';
        }
        std::cout << '\n';

        // delete leftmost value as its something like "game 1" and we're already tracking the game
        current_game.erase(current_game.begin());

        // begin considering the game
        int red_max = 0;
        int green_max = 0;
        int blue_max = 0;

        for(int i = 0; i < current_game.size(); i++)
        {
            std::vector<std::string> split = tokenize_to_vector(current_game[i], " ");
            // now split[0] should equal the num and split[1] should equal the color

            if(split[1] == "red")
            {
                if(stoi(split[0]) > red_max)
                {
                    // valid game
                    red_max = stoi(split[0]);

                }
            }

            if(split[1] == "green")
            {
                if(stoi(split[0]) > green_max)
                {
                    green_max = stoi(split[0]);

                }
            }

            if(split[1] == "blue")
            {
                if(stoi(split[0]) > blue_max)
                {
                    blue_max = stoi(split[0]);

                }
            }
        }
        sum += red_max * green_max * blue_max;
        game++;
    }


    std::cout << "\n" << sum;


    return 0;
}