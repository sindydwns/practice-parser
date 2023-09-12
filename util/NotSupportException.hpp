#ifndef NotSupportException_HPP
#define NotSupportException_HPP

#include <exception>

class NotSupportException : public std::exception
{
public:
    const char *what() const throw();
};

#endif
