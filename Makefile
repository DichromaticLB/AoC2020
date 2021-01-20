CXXFLAGS =	-std=c++1y -O0 -g
OBJS =		AOC2020.o
TARGET =	AOC2020

$(OBJS): AOC2020.cpp Makefile include/*.hpp

$(TARGET):	$(OBJS) 
	$(CXX) -o $(TARGET) $(OBJS) 

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
