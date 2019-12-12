#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

namespace astd {

const int __stl_threshold = 16;

template <class T>
void swap(T& val1, T& val2)
{
    __asm__ ("xchg %0, %1;" : "+r" (val1), "+r" (val2));
    //  GNU C inline asm constraints
    // __asm__ ("":"=g"(val1), "=g"(val2):"1"(val1), "0"(val2));
}

template<class ForwardIt1, class ForwardIt2>
void iter_swap(ForwardIt1 a, ForwardIt2 b)
{
    swap(*a, *b);
    //std::cout << *a << ' ' << *b << "\n";
}

template<typename T>
inline const T& median(const T& a, const T& b, const T& c) {
    if (a > b)
        if (b > c) return b;
            else if (a > c) return c;
                else return a;
        else if (a > c) return a;
            else if (b > c) return c;
                else return b;
}

template <class RandomAccessIterator, class T>
RandomAccessIterator unguarded_partition(RandomAccessIterator first,
                                           RandomAccessIterator last,
                                           T pivot) {
        while (true) {
            while (*first < pivot) ++first;
            --last;
            while (pivot < *last) --last;
            if (!(first < last)) return first;
            //astd::iter_swap(first, last);
            asm volatile("xchg %0, %1;" : "+r" (*first), "+r" (*last));
            ++first;
        }
}

template <class RandomAccessIterator, class T>
void unguarded_linear_insert(RandomAccessIterator last, T value) {
        RandomAccessIterator next = last;
        --next;
        while (value < *next) {
            *last = *next;
            last = next;
            --next;
        }
        *last = value;
}

template <class RandomAccessIterator>
void unguarded_insertion_sort_aux(RandomAccessIterator first,
                                        RandomAccessIterator last) {
    for (RandomAccessIterator i = first; i != last; ++i)
         unguarded_linear_insert(i, int(*i));
}


template <class RandomAccessIterator>
inline void unguarded_insertion_sort(RandomAccessIterator first,
                                    RandomAccessIterator last) {
    unguarded_insertion_sort_aux(first, last);
}

template <class RandomAccessIterator>
inline void linear_insert(RandomAccessIterator first,
                            RandomAccessIterator last) {
    int value = *last;
    if (value < *first) {
        std::copy_backward(first, last, last + 1);
        *first = value;
    }
    else
        unguarded_linear_insert(last, value);
}

template <class RandomAccessIterator>
void insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
    if (first == last) return;
    for (RandomAccessIterator i = first + 1; i != last; ++i)
        linear_insert(first, i);
}

template <class RandomAccessIterator>
void final_insertion_sort(RandomAccessIterator first,
                            RandomAccessIterator last) {
        if (last - first > __stl_threshold) {
            insertion_sort(first, first + __stl_threshold);
            unguarded_insertion_sort(first + __stl_threshold, last);
        }
        else
            insertion_sort(first, last);
}

template <class RandomAccessIterator, class Size>
void introsort_loop(RandomAccessIterator first,
                      RandomAccessIterator last,
                      Size depth_limit) {
        while (last - first > __stl_threshold) {
            if (depth_limit == 0) {
                partial_sort(first, last, last);
                return;
            }
            --depth_limit;

            RandomAccessIterator cut = unguarded_partition
                (first, last, int(median(*first, *(first + (last - first)/2),
                                   *(last - 1))));
            introsort_loop(cut, last, depth_limit);
            last = cut;
        }
}

template<typename _Size>
_Size __lg(_Size __n) {
    _Size __k;
    for (__k = 0; __n != 0; __n >>= 1)
        ++__k;
    return __k - 1;
}

template <class RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last) {
    if (first != last) {
        introsort_loop(first, last, __lg(last - first) * 2);
        final_insertion_sort(first, last);
    }
}
}

const size_t LARGE_SIZE = 1000000;

int main () {

    int x=10, y=20;
    astd::swap(x,y);
    std::cout << x << ' ' << y << '\n';


    std::vector<int> vec = {3, 1, 2, 4, 6, 5, 10, 8, 2};
    astd::iter_swap(vec.begin(), vec.end() - 1);
    astd::sort(vec.begin(), vec.end());

    std::vector<int>::iterator it;
    for (it = vec.begin(); it != vec.end(); it++)
        std::cout << ' ' << *it;
    std::cout << '\n';


    std::vector<int> v(LARGE_SIZE);

    std::generate(v.begin(), v.end(), std::rand);
    auto t1 = Clock::now();
    std::sort(v.begin(), v.end());
    auto t2 = Clock::now();

    std::cout << "Delta t2-t1: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
              << " nanoseconds" << std::endl;

    std::generate(v.begin(), v.end(), std::rand);
    t1 = Clock::now();
    astd::sort(v.begin(), v.end());
    t2 = Clock::now();

    std::cout << "Delta t2-t1: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
              << " nanoseconds" << std::endl;
    return 0;
}
