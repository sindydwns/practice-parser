#ifndef ParseResult_HPP
#define ParseResult_HPP

#include <iostream>
#include <vector>

class ParseResult
{
public:
    virtual ~ParseResult();

    virtual std::string toString() const;
    const std::vector<ParseResult*> &getChildren() const;

    template <typename T>
    std::vector<const T*> searchByType() const {
        std::vector<const T*> res;
        for (typename std::vector<const T*>::const_iterator it = children.begin(); it != children.end(); it++) {
            const T *child = dynamic_cast<T*>(*it);
            if (child != NULL) res.push_back(child);
            else {
                const std::vector<const T*> grandchildren = child->template searchByType<T>();
                res.insert(res.end(), grandchildren.begin(), grandchildren.end());
            }
        }
        return res;
    };

    template <typename T>
    std::vector<const T*> searchByTag(std::string tag) const {
        std::vector<const T*> res;
        for (typename std::vector<const T*>::const_iterator it = children.begin(); it != children.end(); it++) {
            const T *child = dynamic_cast<T*>(*it);
            if (child != NULL) res.push_back(child);
            else {
                const std::vector<const T*> grandchildren = child->template searchByTag<T>(tag);
                res.insert(res.end(), grandchildren.begin(), grandchildren.end());
            }
        }
        return res;
    };

protected:
    ParseResult();
    ParseResult(std::string match);
    ParseResult(std::vector<ParseResult*> children);
    ParseResult(std::string match, std::vector<ParseResult*> children);

    const std::string match;
    const std::vector<ParseResult*> children;

private:
    ParseResult(const ParseResult &rhs);
    ParseResult &operator=(const ParseResult &rhs);

};

#endif
