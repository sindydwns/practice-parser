#ifndef PatternReadAll_HPP
#define PatternReadAll_HPP

#include "APattern.hpp"

class PatternReadAll: public APattern
{
public:
    PatternReadAll();
    ~PatternReadAll();

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
    PatternReadAll(const PatternReadAll &rhs);
    PatternReadAll &operator=(const PatternReadAll &rhs);

    std::string str;
    
};

#endif
