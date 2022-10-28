PROGRAM=VMtranslator
OBJS=VMtranslator.o Parser.o CodeWriter.o
SRCS=$(OBJS:%.o=%.cpp)
HEADERS=AllHeaders.h Parser.h CodeWriter.h
CC=g++
CFLAGS=-g -Wall
LDFLAGS=
LDLIBS=

vpath %.cpp src
vpath %.h include

$(PROGRAM): $(SRCS)
	g++ -g -Wall -o $(PROGRAM) src/*.cpp

# $(PROGRAM): $(OBJS)
# 	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)

# VMtranslator.o: VMtranslator.cpp
# 	$(CC) -c -o VMtranslator.o VMtranslator.cpp



