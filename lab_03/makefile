CC := g++

CFLAGS := -std=c++11 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	CFLAGS += -g3 -ggdb
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

all: app.exe plist.exe

app.exe: interpol.o array.o matrix.o multidim.o plist.o main.o
	$(CC) $^ -o $@

plist.exe: array.o matrix.o plist.o plist_make.o
	$(CC) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o *.exe
