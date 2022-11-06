# Obrigado a
#   https://stackoverflow.com/a/18258352
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
# Obrigado a
#   https://stackoverflow.com/a/16151140
uniq = $(if $1,$(firstword $1) $(call uniq,$(filter-out $(firstword $1),$1)))

CC = gcc
override CFLAGS += -lm -Wall -ggdb3

BUILDIR = build
SRCS = $(subst ./,,$(call rwildcard,.,*.c))
OBJS = $(patsubst %.c, $(BUILDIR)/%.o, $(notdir $(SRCS)))

vpath %.c $(call uniq,$(dir $(SRCS)))

all : pre-main main

$(BUILDIR)/%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)

pre-main:
	@mkdir -p $(BUILDIR)/

main : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	
clean:
	@rm -rf $(BUILDIR)/ main
