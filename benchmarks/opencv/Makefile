# eigen: test_matrix_pseudoinverse.cpp
# 	g++ -std=c++98 -o eigen.o -I../../include/ test_matrix_pseudoinverse.cpp -lopencv_core  -pg
# 	./eigen.o
# 	gprof -b -p ./eigen.o gmon.out > eigen.prof

# CXX:=g++
# CXXFLAGS := -std=c++11 -Wall
# DEPS :=$(shell pkg-config --cflags --libs opencv4)
# TARGET :=test


# SRCS := $(wildcard *.cpp)
# OBJS := $(patsubst %.cpp, %.o, $(SRCS))

# all: $(TARGET)
# $(TARGET): $(OBJS)
# 	$(info $$var is [${var}])
# 	$(CXX) -o $@ $^

# %.o:  %.cpp $(DEPS)
# 	# echo $(DEPS)
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<  $(DEPS)

DEPS :=$(shell pkg-config --cflags --libs opencv4]
g++ -ggdb -pg *.cpp -o * $(DEPS)

clean:
	rm -rf $(TARGET) *.o 

cleanprof:
	rm -f *.prof 
