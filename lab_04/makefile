CC := g++

CFLAGS := -std=c++11 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	CFLAGS += -g3 -ggdb
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

all: plist.exe

plist.exe: plist_make.o
	$(CC) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o *.exe
