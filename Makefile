CC=gcc
CFLAGS= -std=c99 -pedantic -Wall -g3

all: ladder

HWK4= /c/cs223/Hwk4

Trie.o:		~/cs223/Hwk5/Trie.h
Deque.o:   $(HWK4)/Deque.h

#####
# Instructions to link ladder and Trie
#####

ladder: ladder.o Trie.o $(HWK4)/Deque.o
		${CC} ${CFLAGS} -o $@ $^

ladder.o: $(HWK4)/Deque.h

# ladder.o: ladder.c
# 	${cc}${CFLAGS} -c ladder.c
