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

    std::string type;
    std::string tag;

private:
    APattern(const APattern &rhs);
    virtual APattern &operator=(const APattern &rhs);

    bool useTrim;
    bool useIgnoreCase;

};

#endif
