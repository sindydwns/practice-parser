#ifndef PatternReadUntil_HPP
#define PatternReadUntil_HPP

#include "APattern.hpp"

class PatternReadUntil: public APattern
{
public:
    PatternReadUntil(const std::string suffix);
    ~PatternReadUntil();

    virtual ParseStream::CompileResult compile(ParseStream &ps) const;
    PatternReadUntil *setUseSuffix(bool useSuffix);

    struct Data : IData
    {
        Data();
        std::string buffer;
        size_t matchIdx;
    };

private:
    PatternReadUntil();
    PatternReadUntil(const PatternReadUntil &rhs);
    PatternReadUntil &operator=(const PatternReadUntil &rhs);

    std::string str;
    bool useSuffix;
    
};

#endif
