TARGET = POS_semestralnaPraca

CC = gcc

DEBUG = -g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS= client.o server.o

all: $(OBJS)
        $(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

client.o: client.c
        $(CC) -c $(CCFLAGS) client.c $(GTKLIB) -o client.o

server.o: server.c
        $(CC) -c $(CCFLAGS) server.c $(GTKLIB) -o server.o
clean:
        rm -f *.o $(TARGET)