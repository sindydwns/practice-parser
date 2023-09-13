#ifndef PatternEqual_HPP
#define PatternEqual_HPP

#include "APattern.hpp"

class PatternEqual: public APattern
{
public:
    PatternEqual(const std::string str);
    ~PatternEqual();

    virtual ParseStream::State compile(ParseStream &ps) const;

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
    PatternEqual();
    PatternEqual(const PatternEqual &rhs);
    PatternEqual &operator=(const PatternEqual &rhs);

    std::string str;
    
};

#endif
