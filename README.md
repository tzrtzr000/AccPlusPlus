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
- [ ] GSL?

To run opencv, first clone to <__open_cv_dir__>, then run bash to install: 
```bash
git clone https://github.com/opencv/opencv.git. 
cd  <__project_dir_>/AccPlusPlus
./build_open_cv.sh
```

To compile benchmarks  ~~(only eigen for now)~~

Eigen:
```
cd benchmarks
make eigen
./eigen
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

(For arma and opencv benchmark, I removed -O3 flag when compile since gprof cannot work)

Full tutorial <a href="https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html" target="_blank">Pseudo Inverse Test by Nghia Ho's blog</a>  

2. Plot the histogram of leaf function like Figure 3 by [Gope et al](http://pharm.ece.wisc.edu/papers/isca17_dgope.pdf) 

![alt text](./ref/figure_leaf_function.PNG "Logo Title Text 1")

3. Find the "bottleneck" (performance, power, etc)

4. Discuss with Prof. by this Friday (11/22)

