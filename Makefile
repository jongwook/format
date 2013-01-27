UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
format : format.h test.cpp
	g++ -o test test.cpp -std=c++0x
endif

ifeq ($(UNAME), Darwin)
format : format.h test.cpp
	clang++ -o test test.cpp -std=c++0x -stdlib=libc++
endif

clean :
	rm -rf test *.o core 

