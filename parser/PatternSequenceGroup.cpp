#include "PatternSequenceGroup.hpp"

PatternSequenceGroup::PatternSequenceGroup() { }
PatternSequenceGroup::~PatternSequenceGroup()
{
    // TODO delete patterns
}
PatternSequenceGroup::PatternSequenceGroup(const PatternSequenceGroup &rhs) { *this = rhs; }
PatternSequenceGroup &PatternSequenceGroup::operator=(const PatternSequenceGroup &rhs) { (void)rhs; return *this; }

bool PatternSequenceGroup::test(std::stringstream &ss) const
{
    std::streampos pos = ss.tellg();
    for (size_t i = 0; i < this->patterns.size(); i++) {
        if (patterns[i]->test(ss) == false) {
            ss.seekg(pos);
            return false;
        }
    }
    ss.seekg(pos);
    return true;
}

PatternSequenceGroup *PatternSequenceGroup::addPattern(APattern *pattern)
{
    this->patterns.push_back(pattern);
    return this;
}
