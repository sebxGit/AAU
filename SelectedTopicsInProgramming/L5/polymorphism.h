#ifndef SELECTEDTOPICSINPROGRAMMING_POLYMORPHISM_H
#define SELECTEDTOPICSINPROGRAMMING_POLYMORPHISM_H
class Base{
protected:
    int field {};
public:
    virtual void increment() = 0;
    auto decrement() { field--; };
    virtual ~Base() noexcept = default;
};

class Derived : public Base{
    void increment() override { field++; };
};
#endif //SELECTEDTOPICSINPROGRAMMING_POLYMORPHISM_H
