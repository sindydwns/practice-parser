#ifndef ParseCoroutine_HPP
#define ParseCoroutine_HPP

#include <sstream>
#include <stack>
#include <algorithm>
#include "ParseResult.hpp"

class APattern;
class ParseStream : public std::stringstream
{
public:
    ParseStream();
    ParseStream(const ParseStream &rhs);
    ParseStream(const APattern *pattern);
    ~ParseStream();
    ParseStream &operator=(const ParseStream &rhs);

    typedef enum e_state {
        INIT = 0,
        PENDING = 1,
        INVALID = 2,
        VALID = 3
    } State;

    bool isUserEoF() const;
    bool isState(State s) const;
    void setUserEoF();
    void init();
    State yieldReturn(State s, const APattern *p);
    State yieldReturn(State s, std::string &buffer, const APattern *p);
    size_t yieldStackSize();
    std::string yieldContinue(const APattern *p);

    bool next(std::string &str);
    ParseResult &getResult();

private:
    typedef std::pair<const APattern*, std::string> idxPair;

    std::stack<idxPair> indexer;
    const APattern *const pattern;
    ParseResult result;

    bool userEoF;

    State state;

};

#endif
