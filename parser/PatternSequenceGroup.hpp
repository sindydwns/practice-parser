#ifndef PatternSequenceGroup_HPP
#define PatternSequenceGroup_HPP

#include <iostream>
#include <vector>
#include "APattern.hpp"

class PatternSequenceGroup: public APattern
{
public:
    PatternSequenceGroup();
    ~PatternSequenceGroup();

    virtual ParseResult *parse(std::stringstream &ss) const;
    PatternSequenceGroup *addPattern(APattern *pattern);

    class Result: public ParseResult
    {
    public:
        Result(std::vector<ParseResult*> children);

    private:
        Result();
        Result(const Result &rhs);
        Result &operator=(const Result &rhs);
        ~Result();

    };

private:
    PatternSequenceGroup(const PatternSequenceGroup &rhs);
    PatternSequenceGroup &operator=(const PatternSequenceGroup &rhs);
    std::vector<APattern*> patterns;
};

#endif
