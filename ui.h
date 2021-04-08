#ifndef UI_H
#define UI_H

#include "countwords.h"

void checkArgs(int argc, char *argv[], int *numWords, int *flags);
void checkFlag(char *argv[], int *numWords, int i, int *flags);
void scanNum(char *argv[], int *numWords, int i);
void printWords(WORD *words, int numWords, int uniqueWords, int totalWords);
void printSingleWord(WORD *words, int numWords, int i);

#endif
