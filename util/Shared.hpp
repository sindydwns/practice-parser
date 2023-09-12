#ifndef Shared_HPP
#define Shared_HPP

#include <map>

template <typename T>
class Shared
{
public:
    typedef std::map<T*, int> Map;

    Shared(): instance(NULL) { };
    Shared(T *instance): instance(instance) {
        if (isManaged(instance)) throw std::exception();
        counter[instance] = 1;
std::cout << instance << ": "<< counter[instance] << std::endl;
    };
    Shared(const Shared &rhs): instance(rhs.instance) {
        if (isManaged(instance) == false) throw std::exception();
        counter[instance]++;
std::cout << instance << ": "<< counter[instance] << std::endl;
    };
    ~Shared() {
        if (instance == NULL) return;
        if (isManaged(instance) == false) throw std::exception();
        counter[instance]--;
std::cout << instance << ": "<< counter[instance] << std::endl;
        checkDelete(instance);
    };
    Shared &operator=(const Shared &rhs) {
        if (this == &rhs) return *this;
        if (instance != NULL) {
            if (isManaged(instance) == false) throw std::exception();
            counter[instance]--;
std::cout << instance << ": "<< counter[instance] << std::endl;
            checkDelete(instance);
        }
        instance = rhs.instance;
        counter[instance]++;
std::cout << instance << ": "<< counter[instance] << std::endl;
        return *this;
    };
    T *getInstance() const {
        return instance;
    }

private:
    bool isManaged(T *instance) {
        typename Map::iterator it = counter.find(instance);
        return it != counter.end();
    };
    bool checkDelete(T *instance) {
        if (counter[instance] == 0) {
            counter.erase(instance);
            delete instance;
std::cout << instance << ": deleted" << std::endl;
            return true;
        }
        return false;
    };

    static Map counter;
    T *instance;

};

template <typename T>
std::map<T*, int> Shared<T>::counter;

#endif
