#include <vector>
//#include <gperftools/profiler.h>

int foo(std::vector<int> v) {
    int result = 0;
    for(auto x: v) {
        result += x;
    }
    return result;
}

int main() {
//    ProfilerStart("profile.log");
    std::vector<int> v;
    int result = 0;
    for (int i=0; i<20000; i++) {
        result = foo(v);
        v.push_back(result);
    }
 //   ProfilerStop();
    return 1;
}
