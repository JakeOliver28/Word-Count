#ifndef COUNTWORDS_H
#define COUNTWORDS_H

typedef struct {
   int numOcc;
   unsigned len;
   char *name;
} WORD;

void countWords(int argc, char *argv[], WORD **words, int *uniqueWords, int *totalWords, int flags);
int countFile(char *arg, WORD **words, int *mallocSize, int *uniqueWords, int *totalWords, int standardIn);
FILE* openFile(char *arg);
int getWord(FILE *file, char **newWord, unsigned *wordLength, int *isPrintable);
int scanChars(FILE *file, char **newWord, unsigned *wordLen, int *isPrintable);
int checkChar(char **newWord, unsigned *wordLen, int *isPrintable, char ch, int *mallocSize);
void checkNonSpace(char **newWord, unsigned *wordLen, int *isPrintable, char ch, int *mallocSize);
int compareWORD(const void *wordA, const void *wordB);

#define TRUE 1
#define FALSE 0


#endif
