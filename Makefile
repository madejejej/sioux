CXX = clang++
CXXFLAGS = -g -std=c++11 -Wall
LDTESTFLAGS = -lgtest -pthread -L. -lsioux
TESTOBJ = test_main.o
TESTDEPS = test/*.cpp

LDFLAGS = -lboost_system -lboost_thread -L. -fPIC -shared
SRC = src/*.cpp
HEADERS = src/*.hpp
OBJ = $(notdir $(SRC:.cpp=.o))
TARGET = libsioux.so

.PHONY: $(TARGET) all $(OBJ) test $(TESTOBJ) clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $^ $(LDFLAGS)

$(OBJ): $(SRC) 
	$(CXX) -c $^ $(CXXFLAGS)

test: $(TESTOBJ)
	$(CXX) -o tester $^ $(LDTESTFLAGS)
	./tester

$(TESTOBJ): $(TESTDEPS)
	$(CXX) -c $^ $(CXXFLAGS)
	
clean: 
	rm -f *.o