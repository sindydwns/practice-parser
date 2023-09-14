#ifndef PatternEqual_HPP
#define PatternEqual_HPP

#include "APattern.hpp"

class PatternEqual: public APattern
{
public:
    PatternEqual(const std::string str);
    ~PatternEqual();

    virtual ParseStream::CompileResult compile(ParseStream &ps) const;

    struct Data : IData
    {
        Data();
        std::string buffer;
    };

private:
    PatternEqual();
    PatternEqual(const PatternEqual &rhs);
    PatternEqual &operator=(const PatternEqual &rhs);

    std::string str;
    
};

#endif
