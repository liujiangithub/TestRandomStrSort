all: SingleThreadSort MultiThreadSort SingleThreadSortSingleCpu MultiThreadSortSingleCpu

SingleThreadSort: src/RandomStrGenerator.cpp src/RandomStrGenerator.h src/common.h src/SingleThreadSort.cpp
	g++  -std=c++11 -O3 -I./src  -o SingleThreadSort src/RandomStrGenerator.cpp src/SingleThreadSort.cpp

MultiThreadSort: src/RandomStrGenerator.cpp src/RandomStrGenerator.h src/common.h src/SafeThreadQueue.h src/MultiThreadSort.cpp
	g++  -std=c++11 -O3 -I./src  -o MultiThreadSort src/RandomStrGenerator.cpp src/MultiThreadSort.cpp -lpthread

SingleThreadSortSingleCpu: src/RandomStrGenerator.cpp src/RandomStrGenerator.h src/common.h src/SafeThreadQueue.h src/MultiThreadSort.cpp
	g++ -DBIND_CPU -std=c++11 -O3 -I./src  -o SingleThreadSortSingleCpu src/RandomStrGenerator.cpp src/SingleThreadSort.cpp -lpthread

MultiThreadSortSingleCpu: src/RandomStrGenerator.cpp src/RandomStrGenerator.h src/common.h src/SafeThreadQueue.h src/MultiThreadSort.cpp
	g++ -DBIND_CPU -std=c++11 -O3 -I./src  -o MultiThreadSortSingleCpu src/RandomStrGenerator.cpp src/MultiThreadSort.cpp -lpthread

clean:
	rm MultiThreadSort SingleThreadSort SingleThreadSortSingleCpu MultiThreadSortSingleCpu
