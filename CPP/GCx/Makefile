CPPC = g++-10
CPPFLAGS = -Wall -g -std=c++2a -O2

all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp Makefile
	$(CPPC) $(CPPFLAGS) $< -o $@ 

clean: 
	rm -rf *.out