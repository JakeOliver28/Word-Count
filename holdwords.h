#ifndef HOLDWORDS_H
#define HOLDWORDS_H

#include "countwords.h"

void addWord(WORD **words, char *newWord, unsigned wordLen, int isPrintable, int *mallocSize, int *uniqueWords, int *totalWords);
void addPrintableWord(WORD **words, char *newWord, unsigned wordLen, int *mallocSize, int *uniqueWords);
int isSameWord(WORD listWord, char *newWord, unsigned wordLength);
void addNewWord(WORD **words, char *newWord, unsigned wordLen, int *mallocSize, int *uniqueWords, int i);

#endif
