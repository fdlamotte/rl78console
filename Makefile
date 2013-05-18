
LDFLAGS += -lusb -lcurses
CC = gcc

all : rl78console

RL78_CONSOLE_SRC = rl78console.c 
RL78_CONSOLE_SRC += rl78com.c

RL78_CONSOLE_OBJ = $(RL78_CONSOLE_SRC:%.c=%.o)

rl78console: $(RL78_CONSOLE_OBJ)
	$(CC) $(RL78_CONSOLE_OBJ) -o $@ $(LDFLAGS)

clean:
	rm -rf *.o rl78console
