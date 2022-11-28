CC = clang
CFLAGS = -Wall
OBJDIR = out

SRCS = $(wildcard *.c */*.c)
OB = $(notdir $(patsubst %.c,%.o,$(SRCS)))
OBJS = $(addprefix $(OBJDIR)/,$(OB))

all: main

debug:
	@echo 'SRCS: "$(SRCS)"'
	@echo 'OB: "$(OB)"'
	@echo 'OBJS: "$(OBJS)"'

main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ 

# Compile with linked lib
# main: main.o libowl.a
# 	$(CC) $(CFLAGS) -o $@ $^ -L. -lowl

*/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

*/%.o: */%.c
	$(CC) $(CFLAGS) -c -o $@ $<

libowl.a: $(OBJS)
	ar -rcs libowl.a $^

# Todo: add ordered prerequisite to
# create dir out 
# https://www.gnu.org/savannah-checkouts/gnu/make/manual/html_node/Prerequisite-Types.html#Prerequisite-Types
# $(OBJS): | $(OBJDIR)

# $(OBJDIR):
# 	mkdir $(OBJDIR)

.PHONY: clean all

clean:
	rm -rf *.o */*.o main libowl.a