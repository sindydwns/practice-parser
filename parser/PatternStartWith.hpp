#ifndef PatternStartWith_HPP
#define PatternStartWith_HPP

#include "APattern.hpp"

class PatternStartWith: public APattern
{
public:
    PatternStartWith(const std::string str);
    ~PatternStartWith();

    virtual bool test(std::stringstream &ss) const;
    PatternStartWith *setUseTrim(bool useTrim);

private:
    PatternStartWith();
    PatternStartWith(const PatternStartWith &rhs);
    PatternStartWith &operator=(const PatternStartWith &rhs);

    std::string str;
    bool useTrim;
};

#endif
