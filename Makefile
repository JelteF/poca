PROGNAME = poca
SRCFILES = poca.c
RUNARGS =

CC = gcc

WARNFLAGS = -Wall -Wextra
CFLAGS = -std=c99 -O2 $(WARNFLAGS)
LDFLAGS = -lm

OBJECTS = $(SRCFILES:.c=.o)

all: $(PROGNAME)

$(PROGNAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) -I.

.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $<

run: $(PROGNAME)
	./$(PROGNAME) $(RUNARGS)

clean:
	rm -f *.o
	rm -f $(PROGNAME)
