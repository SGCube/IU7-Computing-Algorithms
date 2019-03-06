CC := g++

CFLAGS := -std=c++11 -Wall -Werror -pedantic

OBJS := func.o matrix.o interpol.o main.o

ifeq ($(mode), debug)
    CFLAGS += -g3 -ggdb
endif

ifeq ($(mode), release)
    CFLAGS += -DNDEBUG -g0
endif

app.exe: $(OBJS) main.o
	$(CC) $^ -o $@
	
%.o: %.cpp *.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	$(RM) *.o *.exe
