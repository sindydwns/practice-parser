#ifndef AParseResult_HPP
#define AParseResult_HPP

#include <iostream>
#include <vector>

class AParseResult
{
public:
    virtual std::string toString() const = 0;
    virtual const std::vector<AParseResult*> &children() const = 0;

    template <typename T>
    std::vector<const T*> searchByType() const {
        std::vector<const T*> res;
        const std::vector<AParseResult*> children = this->children();
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
        const std::vector<AParseResult*> children = this->children();
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
    AParseResult();

private:
    AParseResult(const AParseResult &rhs);
    virtual ~AParseResult();
    AParseResult &operator=(const AParseResult &rhs);

};

#endif
