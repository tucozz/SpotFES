# Makefile que percorre todo o projeto, procurando todos os códigos fontes .c para compilar

# INCLUDE - é o diretório que contém os headers
# BUILDIR - é o diretório onde estarão os binários
# LIBDIR - é o diretório onde estara a biblioteca do projeto
# LIB - nome base da biblioteca do projeto
# LIBTARGET - nome completo da biblioteca
# SRCS - lista com os caminhos para todos .c
# OBJS - lista com os caminhos para todos .o
INCLUDE = headers/
BUILDIR = build
LIBDIR = .
LIB = spotfes
LIB_TARGET = $(LIBDIR)/lib$(LIB).a
SRCS = $(shell find src/ -type f -name '*.c' | sed 's|^./||')
OBJS = $(patsubst %.c, $(BUILDIR)/%.o, $(notdir $(SRCS)))

# CCompiler - é o compilador usado
# CFLAGS - são as flags dadas ao compilador durante a compilação
CC = gcc
override CFLAGS += -lm -Wall -pedantic -ggdb3 -I $(INCLUDE)

# ARchive - é o comando arquivador da biblioteca
# ARFLAGS - são as flags dadas ao arquivador
AR = ar
ARFLAGS = rcs

# vpath diretiva que adiciona todos os diretórios com códigos fontes para busca com o padrão %.c
#   - https://www.gnu.org/software/make/manual/html_node/Selective-Search.html
#   - não me pergunte mais nada, eu não sei como funciona
vpath %.c $(shell dirname $(SRCS) | uniq)

all : pre-main main

# Compila todos os .o
$(BUILDIR)/%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(LIBDIR)/lib$(LIB).a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# Preparativos para o build; Garante que o diretório build/ existe
pre-main:
	@mkdir -p $(BUILDIR)/

# Linka todos os .o no executável main
main : $(LIB_TARGET) main.c
	$(CC) -o $@ main.c -L . -l$(LIB) $(CFLAGS)

# Rode make clean para remover tudo que é gerado pelo deploy
clean:
	rm -rf $(BUILDIR)/ main $(LIBDIR)/lib$(LIB).a

valgrind: all
	rm -f valgrind-out.txt

	valgrind --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --verbose \
			 --log-file=valgrind-out.txt \
			 ./main "data/tracks_full.csv" "data/artists_full.csv"

	@echo "Head to valgrind-out.txt"
