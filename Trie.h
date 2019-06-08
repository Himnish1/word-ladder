// Interface of Trie ADT

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct trie *Trie;


/* takes pointer received and sets it to a new empty trie*/
void createT(Trie * t);

/* add a new key to a trie */
/* and return the new trie */
bool insertT(Trie * t, char *attr, char *previous, int steps);

/*search for target in trie and return true if target is found*/
bool searchT(Trie * t, char *target, int * nStps, char ** prevword);

/* free a trie */
void destroyT(Trie * t);
