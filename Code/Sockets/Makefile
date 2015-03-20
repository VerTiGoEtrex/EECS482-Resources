CXXFLAGS := -Wall -Werror -g -std=c++11
LDFLAGS :=

all: client.out server.out

%.out: %.cpp globalFunctions.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *~ *.out
