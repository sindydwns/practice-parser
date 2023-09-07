#include "Consumer.hpp"

Consumer::Consumer() { }
Consumer::~Consumer() { }
Consumer::Consumer(const Consumer &rhs) { *this = rhs; }
Consumer &Consumer::operator=(const Consumer &rhs)
{
    if (this == &rhs) return *this;
    return *this;
}
