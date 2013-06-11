CXX = clang++
CXXFLAGS = -g -std=c++11 -Wall #-stdlib=libc++
LDTESTFLAGS = -L. -lgtest -pthread -lsioux -lboost_thread
TESTOBJ = test_main.o
TESTDEPS = test/*.cpp

LDFLAGS = -lboost_system  -L. -fPIC -shared
SRC = src/*.cpp
HEADERS = src/*.hpp
OBJ = $(notdir $(SRC:.cpp=.o))
TARGET = libsioux.so

.PHONY: $(TARGET) all $(OBJ) test $(TESTOBJ) clean app

all: $(TARGET) app

app: 
	$(CXX) -c src/app/sioux.cpp $(CXXFLAGS)
	$(CXX) -o sioux_app sioux.o -L. -lboost_system -lboost_thread -lboost_program_options -pthread -lsioux

$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $^ $(LDFLAGS)

$(OBJ): $(SRC) 
	$(CXX) -c $^ $(CXXFLAGS) -fPIC

test: $(TESTOBJ)
	$(CXX) -o tester $^ $(LDTESTFLAGS)
	./tester

$(TESTOBJ): $(TESTDEPS)
	$(CXX) -c $^ $(CXXFLAGS)
	
clean: 
	rm -f *.o