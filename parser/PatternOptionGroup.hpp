#ifndef PatternOptionGroup_HPP
#define PatternOptionGroup_HPP

#include <iostream>
#include <vector>
#include "APattern.hpp"

class PatternOptionGroup: public APattern
{
public:
    PatternOptionGroup();
    ~PatternOptionGroup();
    PatternOptionGroup(const PatternOptionGroup &rhs);
    PatternOptionGroup &operator=(const PatternOptionGroup &rhs);

    virtual bool test(std::stringstream &ss) const;

    PatternOptionGroup *addPattern(APattern *pattern);

private:
    std::vector<APattern*> patterns;
};

#endif