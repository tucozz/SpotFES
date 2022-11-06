CC = gcc
override CFLAGS += -lm -Wall -ggdb3

BUILDIR = build
SRCS = $(shell find . -type f -name '*.c' | sed 's|^./||')
OBJS = $(patsubst %.c, $(BUILDIR)/%.o, $(notdir $(SRCS)))

vpath %.c $(shell dirname $(SRCS) | uniq)

all : pre-main main

$(BUILDIR)/%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)

pre-main:
	@mkdir -p $(BUILDIR)/

main : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	
clean:
	@rm -rf $(BUILDIR)/ main
