CXX = clang++
CXXFLAGS = -g
LDFLAGS = -lgtest -pthread
TESTOBJ = main.o
TESTDEPS = test/*.cpp

all:
	sioux test

sioux:


test: $(TESTOBJ)
	$(CXX) -o target/tester main.o $(LDFLAGS)
	target/tester

$(TESTOBJ): $(TESTDEPS)
	$(CXX) -c test/main.cpp $(CXXFLAGS)