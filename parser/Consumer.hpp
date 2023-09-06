#ifndef Consumer_HPP
#define Consumer_HPP

class Consumer
{
public:
    Consumer();
    ~Consumer();
    Consumer(const Consumer &rhs);
    Consumer &operator=(const Consumer &rhs);
};

#endif
