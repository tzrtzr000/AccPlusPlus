	
push_back.prof: push_back.o 
	./push_back.o
	# gprof ./push_back.o gmon.out  >> push_back.prof
	# `pkg-config opencv --cflags --libs` -lopencv_core -lopencv_highgui -lopencv_imgproc  -L/usr/local/lib -lopencv_core  -lopencv_highgui 
	
	# To generate function call graph
	gprof ./push_back.o gmon.out | tee push_back.prof  | gprof2dot  -n0.15 -e0.15| dot -Tpng -o func_dag_t.png 

	
push_back.o: push_back.cpp
	g++ -std=c++11 -o push_back.o push_back.cpp -pg  

default: push_back.o push_back.prof

# To generate function call graph
push_back_line_by_line.o: push_back.cpp
	g++ -std=c++11 -fprofile-arcs -ftest-coverage push_back.cpp
	gcov push_back.cpp
	mv *.gcov gcov_out

clean:
	rm -f *.o *.out

cleanprof:
	rm -f *.prof 