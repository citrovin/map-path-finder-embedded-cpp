#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdexcept>

#include "headers/argparser.h"

ArgParser::ArgParser(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        args_.push_back(argv[i]);
    }
}

std::string ArgParser::getCmdOption(const std::string & option)
{
    auto itr = std::find(args_.begin(), args_.end(), option);
    if (itr != args_.end() && ++itr != args_.end())
    {
        return *itr;
    }
    return 0;
}

bool ArgParser::cmdOptionExists(const std::string& option)
{
    return std::find(args_.begin(), args_.end(), option) != args_.end();
}