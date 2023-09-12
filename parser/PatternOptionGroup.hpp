#ifndef PatternOptionGroup_HPP
#define PatternOptionGroup_HPP

#include <iostream>
#include <vector>
#include "APattern.hpp"

class PatternOptionGroup: public APattern
{
public:
    PatternOptionGroup();
    PatternOptionGroup(size_t minMatch);
    PatternOptionGroup(size_t minMatch, size_t maxMatch);
    ~PatternOptionGroup();

    virtual ParseResult *parse(std::stringstream &ss) const;
    PatternOptionGroup *addPattern(APattern *pattern);

    class Result: public ParseResult
    {
    public:
        Result(std::vector<ParseResult> children);
        virtual std::string toString() const;

    private:
        Result();
        Result(const Result &rhs);
        Result &operator=(const Result &rhs);
        ~Result();

    };

private:
    PatternOptionGroup(const PatternOptionGroup &rhs);
    PatternOptionGroup &operator=(const PatternOptionGroup &rhs);

    std::vector<APattern*> patterns;
    size_t minMatch;
    size_t maxMatch;
};

#endif
