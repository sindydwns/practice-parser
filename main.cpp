#include <iostream>
#include <fstream>
#include <sstream>
#include "parser/Parser.hpp"
#include "parser/PatternOptionGroup.hpp"

int readFile(std::fstream &fs, std::string filename)
{
    fs.open(filename.c_str());
    if (fs.fail()) return 1;
    return 0;
}

int main(int argc, char **argv)
{
    std::fstream in;
    if (argc != 2 || readFile(in, std::string(argv[1]))) return 1;

    std::cout << "--------------------------" << std::endl;
    std::string line;
    while (std::getline(in, line)) {
        std::cout << "> " << line << std::endl;

        Parser parser(
            new PatternOptionGroup()
        );

        ParseResult *res = parser.parse(line);
        if (res != NULL) std::cout << *res << std::endl;
        else std::cout << "[ invalid ]" << std::endl;
            
        delete res;
    }
    return 0;
}
