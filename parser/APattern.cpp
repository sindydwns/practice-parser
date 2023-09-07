#include "APattern.hpp"

APattern::APattern() { }
APattern::~APattern() { }
APattern::APattern(const APattern &rhs) { *this = rhs; }
APattern &APattern::operator=(const APattern &rhs) { (void)rhs; return *this; }

const std::string &APattern::getType()
{
    return this->type;
}

const std::string &APattern::getTag()
{
    return this->tag;
}
