#ifndef PatternWord_HPP
#define PatternWord_HPP

#include "APattern.hpp"

class PatternWord: public APattern
{
public:
    PatternWord();
    ~PatternWord();

    virtual ParseResult *parse(std::stringstream &ss) const;

    class Result: public ParseResult
    {
    public:
        Result(std::string match);

    private:
        Result();
        Result(const Result &rhs);
        Result &operator=(const Result &rhs);
        ~Result();

    };

private:
    PatternWord(const PatternWord &rhs);
    PatternWord &operator=(const PatternWord &rhs);

    std::string str;
    
};

#endif
