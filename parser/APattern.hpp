#ifndef APattern_HPP
#define APattern_HPP

#include <vector>
#include <sstream>
#include "ParseResult.hpp"

class APattern
{
public:
    virtual ~APattern();

    const std::string &getTag() const;
    virtual ParseResult *parse(std::stringstream &ss) const = 0;
    APattern *setTag(std::string &tag);
    APattern *setUseTrim(bool useTrim);
    APattern *setUseIgnoreCase(bool useIgnoreCase);

protected:
    APattern();
    APattern(bool useTrim, bool useIgnoreCase);

    static std::string trim(const std::string &str);
    static std::string toupper(const std::string &str);
    static std::string tolower(const std::string &str);
    bool equal(const std::string &str1, const std::string &str2) const;
    bool equal(const char c1, const char c2) const;

    std::string tag;
    bool useTrim;
    bool useIgnoreCase;

private:
    APattern(const APattern &rhs);
    virtual APattern &operator=(const APattern &rhs);

};

#endif
