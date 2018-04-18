CC = g++
LIBS =  -lm `allegro-config --libs`
CFLAGS = -O -std=c++11 -Wall
OBJS = main.o sound.o vector.o
EXEC = newkind

all: $(EXEC)

clean:
	rm *.o $(EXEC)

.SUFFIXES : .cpp .o

.cpp.o:
	$(CC) $(CFLAGS) -c $<

$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(LIBS) 

main.o: main.cpp

sound.o: sound.cpp sound.hpp

vector.o: vector.cpp vector.hpp
