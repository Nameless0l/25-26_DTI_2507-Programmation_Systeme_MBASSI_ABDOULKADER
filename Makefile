CC = gcc
CFLAGS = -Wall -Wextra -g

MAIN_SRC = main.c utils.c command.c pipe.c
MAIN_OBJ = $(MAIN_SRC:.c=.o)

QUESTIONS = question1 question2 question3 question5 question6 question7 question8

all: enseash $(QUESTIONS)

enseash: $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

question1: question1.c
	$(CC) $(CFLAGS) -o $@ $<

question2: question2.c question1.h
	$(CC) $(CFLAGS) -o $@ question2.c

question3: question3.c question1.h
	$(CC) $(CFLAGS) -o $@ question3.c

question5: question5.c question1.h
	$(CC) $(CFLAGS) -o $@ question5.c

question6: question6.c question1.h
	$(CC) $(CFLAGS) -o $@ question6.c

question7: question7.c question1.h command.c utils.c
	$(CC) $(CFLAGS) -o $@ question7.c command.c utils.c

question8: question8.c question1.h command.c utils.c pipe.c
	$(CC) $(CFLAGS) -o $@ question8.c command.c utils.c pipe.c

indent:
	indent -linux -i4 -nut -ts2 *.c

clean:
	rm -f enseash $(QUESTIONS)
	rm -f *.o

.PHONY: all clean indent
