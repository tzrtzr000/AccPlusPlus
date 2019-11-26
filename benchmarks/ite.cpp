#include <vector>
#include <iterator>

int sum() {
    std::vector<int> arr = { 0, 1, 2, 3, 4, 5 };
    std::vector<int>::iterator ptr = arr.begin(); 
    ptr++;
    /*
    for (ptr = arr.begin(); ptr < arr.end(); ptr++) {
        sum += *ptr;
    }*/
    return 0;
}
