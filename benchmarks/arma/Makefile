atlas: 
	g++ test_matrix_pseudoinverse.cpp -o test_matrix_pseudoinverse.o -L/usr/lib/atlas-base -L/usr/lib/openblas-base -lopencv_core -larmadillo -lgomp -fopenmp -lcblas -llapack_atlas -march=native -pg -DARMA_NO_DEBUG -DNDEBUG -DHAVE_INLINE -DGSL_RANGE_CHECK_OFF
	./test_matrix_pseudoinverse.o
	gprof -b -p ./test_matrix_pseudoinverse.o gmon.out > atlas.prof

openblas: 
	g++ test_matrix_pseudoinverse.cpp -o test_matrix_pseudoinverse.o -L/usr/lib/atlas-base -L/usr/lib/openblas-base -lopencv_core -larmadillo -lgomp -fopenmp -lopenblas -llapack_atlas -march=native -pg -DARMA_NO_DEBUG -DNDEBUG -DHAVE_INLINE -DGSL_RANGE_CHECK_OFF
	./test_matrix_pseudoinverse.o
	gprof -b -p ./test_matrix_pseudoinverse.o gmon.out > openblas.prof

clean:
	rm -f *.o *.out

cleanprof:
	rm -f *.prof 