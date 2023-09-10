#ifndef PatternReadUntil_HPP
#define PatternReadUntil_HPP

#include "APattern.hpp"

class PatternReadUntil: public APattern
{
public:
    PatternReadUntil(const std::string str);
    ~PatternReadUntil();

    virtual bool test(std::stringstream &ss) const;

    PatternReadUntil *setUseStrict(bool useStrict);

private:
    PatternReadUntil();
    PatternReadUntil(const PatternReadUntil &rhs);
    PatternReadUntil &operator=(const PatternReadUntil &rhs);

    std::string str;
    bool useStrict;
    
};

#endif