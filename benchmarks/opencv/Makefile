default: 
	g++ test_matrix_pseudoinverse.cpp -o test_matrix_pseudoinverse.o -lopencv_core -pg
	./test_matrix_pseudoinverse.o
	gprof -b -p ./test_matrix_pseudoinverse.o gmon.out > opencv.prof

clean:
	rm -f *.o *.out

cleanprof:
	rm -f *.prof 