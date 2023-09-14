#ifndef PatternWord_HPP
#define PatternWord_HPP

#include "APattern.hpp"

class PatternWord: public APattern
{
public:
    PatternWord();
    ~PatternWord();

    virtual ParseStream::CompileResult compile(ParseStream &ps) const;

    struct Data : IData
    {
        Data();
        std::string buffer;
        std::string ws;
        bool modeSkipWs;
    };

private:
    PatternWord(const PatternWord &rhs);
    PatternWord &operator=(const PatternWord &rhs);

    std::string str;
    
};

#endif
