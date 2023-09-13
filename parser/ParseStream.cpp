#include "ParseStream.hpp"
#include "APattern.hpp"

ParseStream::ParseStream() : 
    pattern(NULL),
    userEoF(false),
    state(State::INIT) { }

ParseStream::ParseStream(const ParseStream &rhs) :
    pattern(rhs.pattern),
    userEoF(rhs.userEoF),
    state(rhs.state) { }

ParseStream::ParseStream(const APattern *pattern) :
    pattern(pattern),
    userEoF(false),
    state(State::INIT) { }

ParseStream::~ParseStream() { }
ParseStream &ParseStream::operator=(const ParseStream &rhs)
{
    if (this == &rhs) return *this;
    this->~ParseStream();
    new (this) ParseStream(rhs);
    return *this;
}

bool ParseStream::isUserEoF() const { return this->userEoF; }
bool ParseStream::isState(State s) const { return state == s; }
void ParseStream::setUserEoF() { this->userEoF = true; }
void ParseStream::init()
{
    this->clear();
    this->str("");
    result = ParseResult();
    this->userEoF = false;
    this->state = State::INIT;
}

ParseStream::State ParseStream::yieldReturn(State s, const APattern *p)
{
    std::string str;
    return yieldReturn(s, str, p);
}

ParseStream::State ParseStream::yieldReturn(State s, std::string &buffer, const APattern *p)
{
    this->clear();
    if (s == State::PENDING) this->indexer.push(idxPair(p, buffer));
    return s;
}

size_t ParseStream::yieldStackSize() { return indexer.size(); }

std::string ParseStream::yieldContinue(const APattern *p)
{
    const idxPair &pair = this->indexer.top();
    if (pair.first != p) throw std::logic_error("yield continue pattern not match");
    this->indexer.pop();
    return pair.second;
}

bool ParseStream::next(std::string &str) { return this->state != State::INVALID; }
ParseResult &ParseStream::getResult() { return result; }
