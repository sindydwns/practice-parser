#ifndef ParseResult_HPP
#define ParseResult_HPP

#include <exception>
#include <iostream>
#include <vector>

class ParseResult
{
public:
    ParseResult();
    ParseResult(std::string match);
    ParseResult(std::vector<ParseResult> children);
    ParseResult(std::string match, std::vector<ParseResult> children);
    ParseResult(const ParseResult &rhs);
    virtual ~ParseResult();
    ParseResult &operator=(const ParseResult &rhs);

    virtual std::string toString() const;
    const std::vector<ParseResult> &getChildren() const;

    template <typename T>
    std::vector<const T> &searchByType(std::vector<const T> &found) const {
        for (typename std::vector<const T>::const_iterator it = children.begin(); it != children.end(); it++) {
            try {
                const T &child = dynamic_cast<T&>(*it);
                found.push_back(child);
            } catch(const std::bad_cast &e) {
                (void)e;
                dynamic_cast<ParseResult&>(*it).searchByType<T>(found);
            }
        }
        return found;
    };

    template <typename T>
    std::vector<const T> &searchByTag(std::vector<const T> &found, std::string tag) const {
        for (typename std::vector<const T>::const_iterator it = children.begin(); it != children.end(); it++) {
            try {
                const T &child = dynamic_cast<T&>(*it);
                // TODO check tag; if (child.tag != tag) then throw bad_cast exception;
                (void)tag;
                found.push_back(child);
            } catch(const std::bad_cast &e) {
                (void)e;
                dynamic_cast<ParseResult&>(*it).searchByType<T>(found);
            }
        }
        return found;
    };

protected:
    const std::string match;
    const std::vector<ParseResult> children;

private:


};

#endif
