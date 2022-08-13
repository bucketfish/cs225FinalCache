EXENAME = App
OBJS = App.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

# CC = gcc
# CFLAGS = -g -Wall

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

# main: main.o Graph.o Nodes.o _judge.o
# 	$(CC) $(CFLAGS) -o main main.o Graph.o Nodes.o _judge.o

# main.o: main.cpp Graph.h Nodes.h _judge.h
# 	$(CC) $(CFLAGS) -c main.cpp

App.o: App.cpp
	$(CC) $(CFLAGS) -c App.cpp

Nodes.o: main.cpp Nodes.cpp
	$(CXX) $(CXXFLAGS) main.cpp Nodes.cpp

ui.o: main.cpp ui.cpp
	$(CXX) $(CXXFLAGS) main.cpp ui.cpp

Graph.o: main.cpp Graph.cpp
	$(CXX) $(CXXFLAGS) main.cpp Graph.cpp

test: output_msg catch/catchmain.cpp tests/test.cpp Nodes.cpp Graph.cpp
	$(LD) catch/catchmain.cpp tests/test.cpp Nodes.cpp Graph.cpp $(LDFLAGS) -o test

# Graph.o: Graph.h

# Node.o: Node.h

# _judge.o: _judge.h

clean :
	-rm -f *.o $(EXENAME) test
