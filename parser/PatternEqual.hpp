#ifndef PatternEqual_HPP
#define PatternEqual_HPP

#include "APattern.hpp"

class PatternEqual: public APattern
{
public:
    PatternEqual(const std::string str);
    ~PatternEqual();

    virtual bool test(std::stringstream &ss) const;

private:
    PatternEqual();
    PatternEqual(const PatternEqual &rhs);
    PatternEqual &operator=(const PatternEqual &rhs);

    std::string str;
    
};

#endif
