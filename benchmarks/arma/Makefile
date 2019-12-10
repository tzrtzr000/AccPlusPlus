atlas: test_matrix_pseudoinverse.cpp
	g++ test_matrix_pseudoinverse.cpp -o test_matrix_pseudoinverse.o -L/usr/lib/atlas-base -L/usr/lib/openblas-base -lopencv_core -larmadillo -lgomp -fopenmp -lcblas -llapack_atlas -march=native -pg -DARMA_NO_DEBUG -DNDEBUG -DHAVE_INLINE -DGSL_RANGE_CHECK_OFF
	./atlas.o
	gprof -b -p ./atlas.o gmon.out > atlas.prof

openblas: test_matrix_pseudoinverse.cpp
	g++ test_matrix_pseudoinverse.cpp -o test_matrix_pseudoinverse.o -L/usr/lib/atlas-base -L/usr/lib/openblas-base -lopencv_core -larmadillo -lgomp -fopenmp -lopenblas -llapack_atlas -march=native -pg -DARMA_NO_DEBUG -DNDEBUG -DHAVE_INLINE -DGSL_RANGE_CHECK_OFF
	./openblas.o
	gprof -b -p ./openblas.o gmon.out > openblas.prof

clean:
	rm -f *.o *.out

cleanprof:
	rm -f *.prof 