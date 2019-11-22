	
push_back.prof: push_back.o 
	./push_back.o
	gprof ./push_back.o gmon.out  >> push_back.prof
	# gprof ./push_back.o gmon.out | tee push_back.stats_graph  | gprof2dot  -n0 -e0| dot -Tpng -o func_dag.png 
	# `pkg-config opencv --cflags --libs` -lopencv_core -lopencv_highgui -lopencv_imgproc  -L/usr/local/lib -lopencv_core  -lopencv_highgui 

	
push_back.o: push_back.cpp
	g++ -std=c++11 -o push_back.o push_back.cpp -pg  

default: push_back.o push_back.prof

# Line by line compile 
push_back_line_by_line.o: push_back.cpp
	g++ -std=c++11 -fprofile-arcs -ftest-coverage push_back.cpp
	gcov push_back.cpp
	mv *.gcov gcov_out

clean:
	rm -f *.o *.out

cleanprof:
	rm -f *.prof 