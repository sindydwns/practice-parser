#include "NotSupportException.hpp"

const char *NotSupportException::what() const throw()
{
    return "Not Supported";
}
