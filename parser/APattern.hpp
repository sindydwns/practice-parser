#ifndef APattern_HPP
#define APattern_HPP

#include <sstream>

class APattern
{
public:
    virtual ~APattern();
    const std::string &getType();
    const std::string &getTag();
    virtual bool test(std::stringstream &ss) const = 0;
protected:
    APattern();
    std::string type;
    std::string tag;
private:
    APattern(const APattern &rhs);
    virtual APattern &operator=(const APattern &rhs);
};

#endif
