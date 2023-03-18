#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdexcept>

class ArgParser {
public:
    ArgParser(int argc, char* argv[]);
    std::string getCmdOption(const std::string & option);
    bool cmdOptionExists(const std::string& option);
private:
    std::vector<std::string> args_;
};

#endif // ARG_PARSER_H