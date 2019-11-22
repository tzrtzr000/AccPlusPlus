This benchmark contains source code for posts on http://baptiste-wicht.com

Build & Run & Profile
-----

The default target build container benchmark:

    make
    
then, the executables are present in *release/bin/*

To run and profile:

    ./debug/bin/vector_list_update_1 
    gprof [flags(-a, -b, -p...)] ./debug/bin/vector_list_update_1 gmon.out > analysis.txt

profile results are present in *./analysis.txt*

Clarification
-----
1. I removed plf::colony part of this benchmark since we don't need this library right now.
2. The whole benchmark contains many different experiment. I set vector_list_update_1 as the default compile option for convenience. Check makefile for more compiling options. 
3. Since I add *-pg* in compile flag for profiling, all the release options in makefile will not work.
4. The container benchmark code lies in *./src/vector_list_update_1/bench.cpp*, **remember to modify this file to run specific testcase before profiling**! 

License
-------

All the code is licensed under the terms of the MIT license. It means that you
can use this code in your software, even proprietary, as long as you retain the
copyright notice.
