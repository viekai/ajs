TARGET := ajs
INCLUDEDIR := ./include/ 
SRC := $(wildcard src/*.cpp)
CFLAGS := -g -O0

all: $(TARGET) 

$(TARGET) : $(SRC)	
	g++ $(CFLAGS) -I $(INCLUDEDIR) $(SRC) -o $@ 

clean:
	rm -rf ajs *.o
