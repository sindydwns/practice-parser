#include "ParseCoroutine.hpp"

ParseCoroutine::ParseCoroutine() : 
    pattern(NULL),
    eof(false),
    state(State::INIT) { }

ParseCoroutine::ParseCoroutine(const ParseCoroutine &rhs) :
    pattern(rhs.pattern),
    eof(rhs.eof),
    state(rhs.state) { }

ParseCoroutine::ParseCoroutine(const APattern *pattern) :
    pattern(pattern),
    eof(false),
    state(State::INIT) { }

ParseCoroutine::~ParseCoroutine() { }
ParseCoroutine &ParseCoroutine::operator=(const ParseCoroutine &rhs)
{
    if (this == &rhs) return *this;
    this->~ParseCoroutine();
    new (this) ParseCoroutine(rhs);
    return *this;
}

std::stringstream &ParseCoroutine::ss() { return _ss; }
bool ParseCoroutine::isEof() const { return this->eof; }
bool ParseCoroutine::isState(State s) const { return state == s; }
void ParseCoroutine::setEof() { this->eof = true; }
void ParseCoroutine::setFail() { this->state = State::INVALID; }
void ParseCoroutine::init()
{
    _ss.clear();
    _ss.str("");
    result = ParseResult();
    this->eof = false;
    this->state = State::INIT;
}

bool ParseCoroutine::next(std::string &str)
{
    return this->state != State::INVALID;
}

ParseResult &ParseCoroutine::getResult() { return result; }
