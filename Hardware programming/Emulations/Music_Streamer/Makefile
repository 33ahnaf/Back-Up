# all:
# 	ccache g++ -Iinclude src/*.cpp -Wall -Wextra -o bin/app -lasound -lraylib && ./bin/app

CXX := ccache g++
CPPFLAGS := -Iinclude -Wall -Wextra -Wnon-c-typedef-for-linkage
LIBS := -lasound -lraylib

# Get all .cpp files and convert names to bin/*.o
SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:src/%.cpp=bin/%.o)

all: bin/app
		./bin/app

# Link app
bin/app: $(OBJS)
		$(CXX) $(OBJS) -o $@ $(LIBS)

# Compile individual files (This is where ccache shines)
bin/%.o: src/%.cpp | bin
		$(CXX) $(CPPFLAGS) -c $< -o $@

bin:
	mkdir -p bin

clean:
	rm -rf bin
