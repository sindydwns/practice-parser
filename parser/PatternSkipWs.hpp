#ifndef PatternSkipWs_HPP
#define PatternSkipWs_HPP

#include "APattern.hpp"

class PatternSkipWs: public APattern
{
public:
    PatternSkipWs();
    ~PatternSkipWs();

    virtual ParseStream::State compile(ParseStream &ps) const;

private:
    PatternSkipWs(const PatternSkipWs &rhs);
    PatternSkipWs &operator=(const PatternSkipWs &rhs);

    std::string str;
    
};

#endif
