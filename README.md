C program
      % ./ladder INITIAL GOAL DICTIONARY [MAXSTEPS]  
that finds a word ladder connecting an INITIAL word ("wheat" above) and a GOAL word ("grass" above) using words that are also found in the 
file DICTIONARY. A word ladder is a sequence of words in which exactly one letter changes in moving from each word to the next.  

For example,

  wheat => cheat => chest => crest => cress => crass => grass

Ladder uses breadth-first search to find some SHORTEST sequence (if one exists) with at
most MAXSTEPS transitions (default = 10) and prints out the complete sequence of words, each terminated by a newline.

The program makes use of an Abstract Data Type, namely a Trie that contains all possible iterations of the INITIAL word given in the command
line, and use a queue to carry out the breadth-first search.



