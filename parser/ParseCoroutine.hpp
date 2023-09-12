#ifndef ParseCoroutine_HPP
#define ParseCoroutine_HPP

#include <sstream>
#include <stack>
#include "ParseResult.hpp"
#include "APattern.hpp"

class ParseCoroutine
{
public:
    ParseCoroutine();
    ParseCoroutine(const ParseCoroutine &rhs);
    ParseCoroutine(const APattern *pattern);
    ~ParseCoroutine();
    ParseCoroutine &operator=(const ParseCoroutine &rhs);

    std::stringstream &ss();

    typedef enum e_state {
        INIT = 0,
        PENDING = 1,
        INVALID = 2,
        VALID = 3
    } State;

    bool isEof() const;
    bool isState(State s) const;
    void setEof();
    void setFail();
    void init();

    bool next(std::string &str);
    ParseResult &getResult();

private:
    std::stringstream _ss; 
    std::stack<int> indexer;
    std::string buffer;
    const APattern *const pattern;
    ParseResult result;

    bool eof;

    State state;

};

#endif
