#include <iostream>

class Counter
{
private:
    int count = 0;

public:
    void tick() { count++; }
    void reset() { count = 0; }
    int get() { return count; }
    void output() { std::cout << "Count is " << count << std::endl; }
};

int main()
{
    Counter counter;
    counter.tick();
    counter.output();
    std::cout << counter.get() << std::endl;
    return 0;
}