#include <iostream>
#include <fstream>
#include <sstream>
#include "parser/Parser.hpp"
#include "parser/PatternOptionGroup.hpp"
#include "parser/PatternSequenceGroup.hpp"
#include "parser/PatternEqual.hpp"
#include "parser/PatternReadUntil.hpp"

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
            (new PatternOptionGroup())
            ->addPattern((new PatternSequenceGroup())
                ->addPattern(new PatternEqual("Host"))
                ->addPattern(new PatternReadUntil(":"))
                ->addPattern(new PatternReadUntil("\r\n"))
            )
        );

        ParseResult *res = parser.parse(line);
        if (res == NULL) std::cout << "( null )" << std::endl;
        else std::cout << res->toString() << std::endl;
    }
    return 0;
}
