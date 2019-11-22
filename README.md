# AccPlusPlus
Accelerator for C++ STL
source code/output is collected by each profiler 
### TODO (11/19/2018)
For all: 
1. Run gprof on <a href="http://nghiaho.com/?p=1726" target="_blank">Pseudo Inverse Test by Nghia Ho's blog</a> under **_./benchmarks/test_matrix_pseudoinverse.cpp_** on:

- [x] Eigen
- [x] Armadillo + OpenBLAS
- [x] Armadillo + Atlas (no multi-core supportout of the box???)
- [x] OpenCV
- [ ] Replace the content of <a href="https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html" target="_blank">```benchmarks/Wicht_STL_synthetic/Makefile``` </a>.

To run opencv, first clone to <__project_dir__> (parent dir of AccPlusPlus), then run bash to install: 
```bash
cd ../
git clone https://github.com/opencv/opencv.git. 
cd  AccPlusPlus
./build_open_cv.sh
```

To compile & generate profiled benchmark data

Eigen:
```
cd benchmarks/eigen
make 
```

Armadillo + OpenBLAS:
```
cd benchmarks/arma
make openblas
```

Armadillo + Atlas:
```
cd benchmarks/arma
make altas
```

OpenCV
```
cd benchmarks/opencv
make
```


(FrankieD4C: For arma and opencv benchmark, I removed -O3 flag when compile since gprof cannot work)

Full tutorial <a href="https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html" target="_blank">Pseudo Inverse Test by Nghia Ho's blog</a>  

2. Plot the histogram of leaf function like Figure 3 by [Gope et al](http://pharm.ece.wisc.edu/papers/isca17_dgope.pdf) 

![alt text](./ref/figure_leaf_function.PNG "leaf function distribution")

3. Find the "bottleneck" (performance, power, etc)

    - [ ] Granularity of the analysis: Memory address, Memory size, leaf function, "semantic operations" (what the program mainly does) 

4. Discuss with Prof. by this Friday (11/22)

    - [ ] Memory slab plot for memory allocation like Figure  8(a), similar to the idea of "heap manager" for PHP acceleration. 

    ![alt text](./ref/mem_slob_cdf.PNG "memory slabs' CDF")

    - [ ] "psudo-deep copy" upon value assignment (Lvalue vs Rvalue)
