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

    virtual ParseStream::State compile(ParseStream &ps) const;
    PatternOptionGroup *addPattern(APattern *pattern);

private:
    PatternOptionGroup(const PatternOptionGroup &rhs);
    PatternOptionGroup &operator=(const PatternOptionGroup &rhs);

    std::vector<APattern*> patterns;
    size_t minMatch;
    size_t maxMatch;
};

#endif
