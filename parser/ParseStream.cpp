#include "ParseStream.hpp"
#include "APattern.hpp"

ParseStream::ParseStream() : 
    pattern(NULL),
    streamEoF(false),
    state(State::INIT) { }

ParseStream::ParseStream(const ParseStream &rhs) :
    pattern(rhs.pattern),
    streamEoF(rhs.streamEoF),
    state(rhs.state) { }

ParseStream::ParseStream(const APattern *pattern) :
    pattern(pattern),
    streamEoF(false),
    state(State::INIT) { }

ParseStream::~ParseStream() { }
ParseStream &ParseStream::operator=(const ParseStream &rhs)
{
    if (this == &rhs) return *this;
    this->~ParseStream();
    new (this) ParseStream(rhs);
    return *this;
}

bool ParseStream::isStreamEoF() const { return this->streamEoF; }
bool ParseStream::isState(State s) const { return state == s; }
void ParseStream::turnOnStreamEoF() { this->streamEoF = true; }
void ParseStream::init()
{
    this->clear();
    this->str("");
    result = ParseResult();
    this->streamEoF = false;
    this->state = State::INIT;
}

IData *ParseStream::load()
{
    if (this->indexer.size() == 0) return NULL;
    IData *data = this->indexer.top();
    this->indexer.pop();
    return data;
}

ParseStream::CompileResult ParseStream::yield(IData *data)
{
    this->clear();
    this->indexer.push(data);
    return CompileResult(PENDING);
}

ParseStream::CompileResult ParseStream::yield(IData *data, std::streampos &pos)
{
    this->clear();
    this->seekg(pos);
    this->indexer.push(data);
    return CompileResult(PENDING);
}

ParseStream::CompileResult ParseStream::done(IData *deleteTarget)
{
    this->clear();
    delete deleteTarget;
    return CompileResult(VALID_NO_RES);
}


ParseStream::CompileResult ParseStream::done(ParseResult res, IData *deleteTarget)
{
    this->clear();
    delete deleteTarget;
    return CompileResult(VALID, res);
}

ParseStream::CompileResult ParseStream::drop(std::streampos &pos, IData *deleteTarget)
{
    this->clear();
    this->seekg(pos);
    delete deleteTarget;
    return CompileResult(INVALID);
}

bool ParseStream::next(std::string &str) { return this->state != State::INVALID; }
ParseResult &ParseStream::getResult() { return result; }

ParseStream::CompileResult::CompileResult(State state)
    : state(state) { }
ParseStream::CompileResult::CompileResult(State state, ParseResult result)
    : state(state), result(result) { }
