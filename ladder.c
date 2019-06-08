//Word ladder program by Himnish Hunma

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "/c/cs223/Hwk4/Deque.h"
#include "Trie.h"

// Print message to stderr and exit.
#define DIE(msg)    exit (fprintf (stderr, "%s\n", msg))

// Print error message unless COND is true
#define ORDIE(cond,msg)     if (cond) ; else DIE(msg)

int wordladder(char * initial, char * goal, long maxsteps, struct trie * test) {
	struct deque * q, *stack; //queue to store variations and stack to store word ladder
	struct trie * searchtable;
	createT(&searchtable);
	int DONE = 0;

	char * s;
	char ** current = &s; // will keep track of head of queue being processed

	int zero = 0;
	int * steps = &zero; //wil keep track of the no. of steps associated to a word

	char * smth;
	char ** prevword = &smth; //will keep track of reached from attribute of a word

	int zeros = 0;
	int * stepss = &zeros; //wil keep track of the no. of steps associated to a word

	char * smths;
	char ** prevwords = &smths;

	createD(&q);
	createD(&stack);

	// printf("*%s*", initial);
	// printf("*%s*", goal);

	char * alphabet = "abcdefghijklmnopqrstuvwxyz";
	addD(&q, initial);
	char * dup2 = NULL;
	insertT(&searchtable, strdup(initial), NULL, 0);
	//I need a while loop to pop the head of the queue and do the variations
	while (!(isEmptyD(&q))) {
		if (DONE != 0) break;
		remD(&q, current); //pop head
		searchT(&searchtable, *current, steps, prevword); //initialise steps
		if ((*steps) < maxsteps) {
			for (int i = 0; i < strlen(initial); i++) { // go to every letter
				if (DONE != 0) break; //flag indicating whether goal was found
				for (int j = 0; j < 26; j++) { // changing every letter
					char * nextcopy = strdup(*current);
					nextcopy[i] = alphabet[j];
					if (strcmp(nextcopy, *current) == 0) { //check whether variation is 
						free(nextcopy);
						continue;
					}
					if (strcmp(nextcopy, goal) == 0){
						searchT(&searchtable, *current, steps, prevword);
						char * dup =  strdup(nextcopy);
						free(nextcopy);
						insertT(&searchtable, dup, *current, ++(*steps));
						while (dup != NULL) {
							pushD(&stack, dup);
							//printf("%s\n", nextcopy);
							searchT(&searchtable, dup, stepss, prevwords);
							dup = *prevwords;
						}
						//pushD(&stack, nextcopy);
						DONE++;
						break;

					} else if (searchT(&test, nextcopy, steps, prevword)) {
						if (!(searchT(&searchtable, nextcopy, stepss, prevword))){
							searchT(&searchtable, *current, steps, prevword);
							dup2 = strdup(nextcopy);
							insertT(&searchtable, dup2, *current, (*(steps) + 1));
							addD(&q, dup2);
						}
						else {
							free(nextcopy);
							continue;
						}
					} 
					

					free(nextcopy);

				}
			}
		}
		else break;
	}
	if (DONE == 0) {
		exit(0); //shouldn't I be printing to stderr?
	}

	char * line;
	char ** result = &line;
	while (!(isEmptyD(&stack))) {
		popD(&stack, result);
		printf("%s\n", *result);
	}
	
	
	//destroyT(&searchtable);
	destroyT(&test);
	destroyD(&q);
	destroyD(&stack);
	exit(0);
}

/*find goal
get its prevword and set it to a char *
while prev word and initial is not equal to zero 
search the prev word and get its prevword
put goal in stack
put each prev word in another data structure eg. a stack then pop from the head
and print*/

int main (int argc, char * argv[]) {
	char * initial = argv[1], *goal = argv[2];
	long maxsteps;
	char * endpt;
	int NOMAX = 0; //flag to see if maxsteps is specified
	if (argc != 5 && argc != 4) {
		DIE("Invalid number of arguments");
	}
	if (argc == 4) {
		maxsteps = 10;
		NOMAX = 1;
	}
	else if ((strtol(argv[4], &endpt, 10))<0){
		DIE("Negative MAXSTEPS");
	}
	else maxsteps = strtol(argv[4], &endpt, 10);
	FILE * fp;
	//creating the trie
	struct trie * test;
	createT(&test);

	int nlettersI = 0;
	int nlettersG = 0;

	for (int i = 0; i < strlen(initial); i++) {
		if (isalpha(initial[i]) != 0) {
			nlettersI++;
		}
	}
	for (int i = 0; i < strlen(goal); i++) {
		if (isalpha(goal[i]) != 0) {
			nlettersG++;
		}
	}

	if (nlettersG != nlettersI) DIE("Initial and goal have different lengths");
	
	if (NOMAX == 0) {
		for (int i = 0; i < strlen(argv[4]); i++) {
			if (isdigit(argv[4][i]) == 0) {
				DIE("Invalid MAXSTEPS");
			}
		}
	}
	if (strcmp(argv[3], "-") == 0) {
		char * line = NULL;
		size_t length = 0;
		int actuallen = 0;
		for (int i = 0; i < strlen(initial); i++) {
			if (isalpha(initial[i]) != 0) {
				actuallen++;
			}
		}
		while (0 <= getline(&line, &length, stdin)) {
			int j = 0;
			char c;
			for (int i = 0; i < strlen(line); i++) {
				if (isalpha(line[i]) != 0) {
					if (isupper(line[i]) != 0) {
						c = tolower(line[i]);
						line[j++] = c;
					}
					else {
						c = line[i];
						line[j++] = c;
					}
				}
			}
			line[j] = '\0';
			
			if (strlen(line) == actuallen) insertT(&test, strdup(line), NULL, 0);
		}
		free(line);
	}
	else {
		char * line = NULL;
		size_t length = 0;
		int actuallen = 0;
		for (int i = 0; i < strlen(initial); i++) {
			if (isalpha(initial[i]) != 0) {
				actuallen++;
			}
		}
		if ((fp = fopen(argv[3], "r"))) {
			while (0 <= getline(&line, &length, fp)) {
				int j = 0;
				char c;
				for (int i = 0; i < strlen(line); i++) {
					if (isalpha(line[i]) != 0) {
						if (isupper(line[i]) != 0) {
							c = tolower(line[i]);
							line[j++] = c;
						}
						else {
							c = line[i];
							line[j++] = c;
						}
					}
				}
				line[j] = '\0';
				
				if (strlen(line) == actuallen) insertT(&test, strdup(line), NULL, 0);
			}
			
			free(line);
		}
		else DIE("Cannot open file");
	}
	//checking if the args are in the dictionary
	char * line;
	char ** result = &line;

	int zero = 0;
	int * step = &zero;

	// char*initialcopy = strdup(initial);
	// char*goalcopy = strdup(goal);

	// printf("*%s*", initial);
	// printf("*%s*", goal);

	int k = 0;
	char d;

	for (int i = 0; i < strlen(initial); i++) {
		if (isalpha(initial[i]) != 0) {
			d = initial[i];
			initial[k++] = d;
		}
	}
	initial[k] = '\0';
	k = 0;
	for (int i = 0; i < strlen(goal); i++) {
		if (isalpha(goal[i]) != 0) {
			d = goal[i];
			goal[k++] = d;
		}
	}
	goal[k] = '\0';
	//printf("*%s*", initial);
	if (!(searchT(&test, initial, step, result))) {
	 	DIE("Word not in dictionary");
	}
	if (!(searchT(&test, goal, step, result))) {
	 	DIE("Word not in dictionary");
	}

	if (strcmp(initial, goal) == 0) printf("%s\n", initial);
	
	// printf("*%s*", initial);
	// printf("*%s*", goal);
	wordladder(initial, goal, maxsteps, test);

	exit(0);
}
