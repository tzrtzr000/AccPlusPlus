#include <iostream>
#include <string>
#include <sstream>
#include <inttypes.h>
#include <cassert>
#include <memory>
#include <stdexcept>
#include <vector>

#define test 500000
// #define test 1000000
using namespace std; //declare for visability so, use cout instead of std::cout



int main(){
	
	vector<int> cache;
	for (int i = 0; i < test; i++){
		cache.push_back(i);
	}

	for(auto it = cache.begin(); it != cache.end(); it++){
		cout<< *it <<endl;
	}

	// fill(cache.begin(), cache.end(), 0);

	// for(auto it = cache.begin(); it != cache.end(); it++){
	// 	cout<< *it <<endl;
	// }

	exit(0);
}
