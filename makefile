CXX=g++
CXXFLAGS= -g -Iinclude -std=c++17
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)
TARGET=main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)
