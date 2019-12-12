#include <iostream>
#include <vector>

template <class RandomAccessIterator>
void iterpp(RandomAccessIterator& it) {
    asm volatile("add $4, %%rax" : "+r" (it));
}

int main() {
    std::vector<int> vec = {1, 2, 4, 6, 5};
    std::vector<int>::iterator it;
    for (it = vec.begin(); it < vec.end(); iterpp(it)) {
        std::cout << *it << "\n";
    }
}
