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

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: */%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

libowl.a: $(OBJS)
	ar -rcs libowl.a $^

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: clean all

clean:
	rm -rf *.o */*.o main libowl.a $(OBJDIR)