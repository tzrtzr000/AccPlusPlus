eigen: test_matrix_pseudoinverse.cpp
	g++ -std=c++98 -o eigen -I../include/ test_matrix_pseudoinverse.cpp `pkg-config opencv --cflags --libs` -lopencv_core -lopencv_highgui -lopencv_imgproc  -L/usr/local/lib -lopencv_core  -lopencv_highgui 2>&1 | tee eigen.log

