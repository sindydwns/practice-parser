#ifndef ParseState_HPP
#define ParseState_HPP

class ParseState
{
public:
    const static int init = 0;
    const static int pending = 1;
    const static int invalid = 2;
    const static int valid = 3;

public:
    int state;

};

#endif
