#include <iostream>
#include <fstream>
#include <sstream>
#include "parser/Parser.hpp"
#include "parser/PatternOptionGroup.hpp"
#include "parser/PatternSequenceGroup.hpp"
#include "parser/PatternEqual.hpp"
#include "parser/PatternReadUntil.hpp"
#include "parser/PatternWord.hpp"
#include "parser/PatternReadAll.hpp"

void test()
{
    std::string file;

    file += "GET /index.html HTTP/1.1\n";
    file += "Host: www.example.com\n";
    file += "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36\n";
    file += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\n";
    file += "Accept-Language: en-US,en;q=0.5\n";
    file += "Accept-Encoding: gzip, deflate\n";
    file += "Connection: keep-alive\n";
    file += "\n";
    file += "body";

    PatternSequenceGroup *startline = new PatternSequenceGroup("startline");
    startline->addPattern(new PatternWord("method"));
    startline->addPattern(new PatternWord("route"));
    startline->addPattern(new PatternWord("http-version"));
    PatternSequenceGroup *header = new PatternSequenceGroup("header");
    header->addPattern(new PatternReadUntil(":", "\n", "key"));
    header->addPattern(new PatternReadUntil("\n", "value"));
    PatternOptionGroup *headers = new PatternOptionGroup(0, 999, "headers");
    headers->addPattern(header);
    PatternReadAll *body = new PatternReadAll("body");
    PatternSequenceGroup *req = new PatternSequenceGroup("req");
    req->addPattern(startline);
    req->addPattern(new PatternEqual("\n", "nextline"));
    req->addPattern(headers);
    req->addPattern(new PatternEqual("\n", "nextline"));
    req->addPattern(body);

    std::stringstream ss(file);
    ss >> std::noskipws;

    Parser parser(req);
    ParseStream stream = parser.makeStream();

    std::string str;
    while (stream.next(str)) {
        char c;
        ss >> c;
        if (ss.eof()) {
            stream.turnOnStreamEoF();
            str = "";
            stream.next(str);
            break;
        }
        std::cout << c;
        str = c;
    }
    std::cout << std::endl;
    ParseResult res = stream.getResult();
    if (stream.isState(INVALID)) std::cout << "( fail )" << std::endl;
    else std::cout << res.toString() << std::endl;
}

int readFile(std::fstream &fs, std::string filename)
{
    fs.open(filename.c_str());
    if (fs.fail()) return 1;
    return 0;
}

#include "util/Shared.hpp"
void testSharedPtr()
{
    std::cout << std::endl << "--- init ---" << std::endl;
    Shared<Parser> a = Shared<Parser>(new Parser(NULL));
    Shared<Parser> b = Shared<Parser>(new Parser(NULL));
    std::cout << std::endl << "--- block in ---" << std::endl;
    {
        Shared<Parser> c = a;
        c = b;
    }
    std::cout << std::endl << "--- block out ---" << std::endl;
}

void leakcheck()
{
    system("leaks main");
}

int main(int argc, char **argv)
{
    // atexit(leakcheck);
    // testSharedPtr();
    std::fstream in;
    if (argc != 2 || readFile(in, std::string(argv[1]))) {
        test();
        return 0;
    }

    // std::cout << "--------------------------" << std::endl;
    // std::string line;
    // while (std::getline(in, line)) {
    //     std::cout << line << std::endl;

    //     Parser parser(
    //         (new PatternOptionGroup(1))
    //         ->addPattern((new PatternSequenceGroup())
    //             ->addPattern((new PatternReadUntil(":")))
    //             ->addPattern(new PatternReadUntil("\n"))
    //         )
    //     );

    //     ParseResult *res = parser.parse(line);
    //     if (res == NULL) std::cout << "> ( null )" << std::endl;
    //     else {
    //         std::cout << "> " << res->toString() << std::endl;
    //         delete res;
    //     }
    // }
    return 0;
}
