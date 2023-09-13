#ifndef PatternWord_HPP
#define PatternWord_HPP

#include "APattern.hpp"

class PatternWord: public APattern
{
public:
    PatternWord();
    ~PatternWord();

    virtual ParseStream::State compile(ParseStream &ps) const;

private:
    PatternWord(const PatternWord &rhs);
    PatternWord &operator=(const PatternWord &rhs);

    std::string str;
    
};

#endif
