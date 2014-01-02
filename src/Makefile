type:=debug
arch:=sm_13
SOURCES:= main_test.cpp my.cpp
HEADERS:=storage.h defs.h
OBJECTS:=$(SOURCES:.cpp=.o)
OBJECTS:=$(OBJECTS:.cu=.o)
OBJECTS:=$(addprefix ../objects/$(type)/, $(OBJECTS))
all: main_test
main_test: $(notdir $(OBJECTS))
	g++ -Wall $(OBJECTS) -o ../bin/$(type)/test -L/usr/local/cuda-5.0/lib64 -lcudart
#VPATH := ./
%.o: %.cpp
	g++ -Wall -MD -c $^ -o $(addprefix ../objects/$(type)/,$@) -I/usr/local/cuda-5.0/include
%.o: %.cu
	/usr/local/cuda-5.0/bin/nvcc -Wall -MD -Xptxas -v -c -arch=$(arch) $< -o $@ 
clean: del_main_test
del_main_test:
	rm -f ../objects/$(type)/*.o ../objects/$(type)/*.d ../bin/$(type)/test
-include $(OBJECTS:.o=.d)
