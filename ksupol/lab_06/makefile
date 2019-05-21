CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic 

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

app.exe : err.o function.o matrix.o main.o
	$(CC) $^ -o $@

table.exe : function.o add_func.o
	$(CC) $^ -o $@
	
%.o : %.c
	$(CC) $(CFLAGS) -c $<
	
clean :
	$(RM) *.o *.exe