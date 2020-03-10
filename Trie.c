// Implementation of Trie ADT

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Trie.h"

// Print message to stderr and exit.
#define DIE(msg)    exit (fprintf (stderr, "%s\n", msg))

// Print error message unless COND is true
#define ORDIE(cond,msg)     if (cond) ; else DIE(msg)

int max = 0;

struct trie {
	char * word;
	char * prevword;
	int nsteps;
	struct trie * children[26];
};

void createT(Trie * t) {
	*t = malloc(sizeof(struct trie));
	for (int i = 0; i < 26; i++) {
		(*t)->children[i] = NULL;			//initialising array to NULL
	}
	(*t)->word = NULL;
	(*t)->prevword = NULL;
	(*t)->nsteps = 0;
}

bool insertT(Trie * t, char *attr, char *previous, int steps) {
	if (max > 65536) DIE("too many inserts");
	max++;
	struct trie * current = *t;
	for (int i = 0; i < strlen(attr); i++) {
		int key = attr[i] - 'a';
		if (current == NULL) DIE("current is null");
		
		if ((current->children[key]) == NULL) {
			//malloc the new 
			current->children[key] = malloc(sizeof(struct trie));
			for (int j = 0; j < 26; j++) {
				current->children[key]->children[j] = NULL;	//initialising array to NULL
			}
			current = current->children[key];
			current->word = NULL;
			current->prevword = NULL;
			current->nsteps = 0;

		}
		else {
			current = current->children[key];
		}
	}
	if (current->word != NULL) return true;
	else current->word = attr;
	if (current->prevword != NULL) return true;
	else current->prevword = previous;
	current->nsteps = steps;
	return true;
}

bool searchT(Trie * t, char *target, int * nStps, char ** prevword){
	struct trie * current = *t;
	for (int i = 0; i < strlen(target); i++) {
		int key = target[i] - 'a';
		if ((current->children[key]) == NULL) {
			*nStps = 0;
			*prevword = NULL;
			return false;
		}
		else current = current->children[key];
	}
	if (current->word == NULL) {
		*nStps = 0;
		*prevword = NULL;
		return false;
	}
	else {
		*prevword = current->prevword;
		*nStps = current->nsteps;
		return true;
	}
}

void destroyT(Trie * t) {
	Trie current = *t; //check if t is null
	for (int i = 0; i < 26; i++) {
		if ((current->children[i]) == NULL) {
			continue;
		}
		destroyT(&(current->children[i]));
	}
	if ((current->word) != NULL) free(current->word);
	if ((current->prevword) != NULL) free(current->prevword);
	free(current);
}

