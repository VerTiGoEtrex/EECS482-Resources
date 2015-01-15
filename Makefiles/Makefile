CXXFLAGS := -Wall -Werror -g -std=c++11 -fwrapv
LDFLAGS := -ldl

VMOBJS = libvm_pager.a
APPOBJS = libvm_app.a
TESTS_SRC=$(wildcard test*.cc)
TESTS = $(patsubst %.cc,%.out,$(TESTS_SRC))
VMLIB = pager.out

all: $(VMLIB) tests

debug: CXXFLAGS += -DDO_VALGRIND #Sets the "DO_VALGRIND" define
debug: CXXFLAGS += -DDEBUG_BUILD #Sets the "DEBUG_BUILD" define
debug: all

pager.out: pager.cc
	$(CXX) $(CXXFLAGS) -o $@ $^ $(VMOBJS) $(LDFLAGS)

tests: $(TESTS)

test%.o: test%.cc #Matches all files starting with "test" and ending in ".cc"
	$(CXX) $(CXXFLAGS) -c $< $(LDFLAGS)

test%.out: test%.o #Matches all files starting with "test" and ending in ".o"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(APPOBJS) $(LDFLAGS)

clean: #Deletes all built files
	rm -f *~ *.out *.o