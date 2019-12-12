// fill algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::fill
#include <vector>       // std::vector
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

namespace astd {
    template <class ForwardIterator, class T>
    void inline fill (ForwardIterator first, ForwardIterator last, const T& val) {
        while (first != last) {
            *first = val;
            //iterpp(first);
            asm volatile("add $4, %%rax" : "+r" (first));
        }
    }

    template <class ForwardIterator, class T>
    void inline fill2 (ForwardIterator first, ForwardIterator last, const T& val) {
        while (first != last) {
            *first = val;
            ++first;
        }
    }
}

const size_t LARGE_SIZE = 1000000;

int main () {
    std::vector<int> myvector (8);                       // myvector: 0 0 0 0 0 0 0 0

    std::fill (myvector.begin(),myvector.begin()+4,5);   // myvector: 5 5 5 5 0 0 0 0
    astd::fill (myvector.begin()+3,myvector.end()-2,8);   // myvector: 5 5 5 8 8 8 0 0

    std::cout << "myvector contains:";
    for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    std::vector<int> v(LARGE_SIZE);

    auto t1 = Clock::now();
    astd::fill2(v.begin(), v.end(), 2);
    auto t2 = Clock::now();

    std::cout << "Delta t2-t1: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
              << " nanoseconds" << std::endl;

    std::vector<int> v1(LARGE_SIZE);

    t1 = Clock::now();
    astd::fill(v1.begin(), v1.end(), 1);
    t2 = Clock::now();

    std::cout << "Delta t2-t1: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
              << " nanoseconds" << std::endl;


  return 0;
}