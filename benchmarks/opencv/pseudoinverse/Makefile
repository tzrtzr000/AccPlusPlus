opencv: 
	g++ test_matrix_pseudoinverse.cpp -o opencv.o -lopencv_core -pg
	./opencv.o
	gprof -b -p ./opencv.o gmon.out > opencv.prof

clean:
	rm -f *.o *.out

cleanprof:
	rm -f *.prof 