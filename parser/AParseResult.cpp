#include "AParseResult.hpp"

AParseResult::AParseResult() { }
AParseResult::AParseResult(const AParseResult &rhs) { *this = rhs; }
AParseResult::~AParseResult() { }
AParseResult &AParseResult::operator=(const AParseResult &rhs)
{
    if (this == &rhs) return *this;
    return *this;
}
