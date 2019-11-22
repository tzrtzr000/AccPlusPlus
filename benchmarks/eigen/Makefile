eigen: ../test_matrix_pseudoinverse.cpp
	g++ -std=c++98 -o eigen.o -I../../include/ ../test_matrix_pseudoinverse.cpp -lopencv_core | tee eigen.log
	./eigen.o
	gprof -b -p ./eigen.o gmon.out > opencv.prof

clean:
	rm -f *.o *.out

cleanprof:
	rm -f *.prof 

