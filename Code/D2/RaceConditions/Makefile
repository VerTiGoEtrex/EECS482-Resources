CXXFLAGS := -Wall -Werror -O3 -std=c++11 
LDFLAGS := -ldl -pthread

OBJS = thread.o libcpu.a

all: tally

tally: tally.o
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) $^

tally.o: tally.cc
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f tally.o tally *~
