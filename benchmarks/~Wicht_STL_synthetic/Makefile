default: 
	g++ test_matrix_pseudoinverse.cpp -o test_matrix_pseudoinverse.o -pg
	./test_matrix_pseudoinverse.o
	gprof -b -p ./test_matrix_pseudoinverse.o gmon.out > wicht_STL_synthetic.prof

clean:
	rm -f *.o *.out

cleanprof:
	rm -f *.prof 