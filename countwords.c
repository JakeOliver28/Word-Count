#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "countwords.h"
#include "holdwords.h"


// Counts the words in all of the files
// Checks for stdin input first and then checks for files
void countWords(int argc, char *argv[], WORD **words, int *uniqueWords, int *totalWords, int flags){
   int i;
   int mallocSize = 10;
   *words = (WORD * ) malloc(mallocSize * sizeof(WORD));

   // If there is input in stdin, count words in stdin
   if ((flags+1) >= argc)
      countFile(*argv, words, &mallocSize, uniqueWords, totalWords, TRUE);
   // Count the words in the files
   for (i = 1; i < argc; i++){
      countFile(argv[i], words, &mallocSize, uniqueWords, totalWords, FALSE);
   }
   *words = (WORD * ) realloc(*words, (*uniqueWords) * sizeof(WORD));
}

// Counts the words in an individual file
int countFile(char *arg, WORD **words, int *mallocSize, int *uniqueWords, int *totalWords, int standardIn){
   FILE *file;
   char *newWord = NULL;
   unsigned wordLength = 0;
   int isPrintable;
   if (standardIn == TRUE)
      file = stdin;
   else if ((file = openFile(arg)) == NULL)
      return 0;
   while (EOF != getWord(file, &newWord, &wordLength, &isPrintable))
      addWord(words, newWord, wordLength, isPrintable, mallocSize, uniqueWords, totalWords);
   addWord(words, newWord, wordLength, isPrintable, mallocSize, uniqueWords, totalWords);
   return 0;
}

// Opens the given file and returns it. If a flag is given, return NULL.
FILE* openFile(char *arg){
   FILE *file;
   if (arg[0] == '-')
      return NULL;
   if ((file = fopen(arg, "r")) == NULL){
      fprintf(stderr, "wf: ");
      perror(arg);
      exit(EXIT_FAILURE);
   }
   return file;
}

// Retrieves a word from file and stores it in the newWord character double pointer.
int getWord(FILE *file, char **newWord, unsigned *wordLength, int *isPrintable){
   *isPrintable = FALSE;
   *wordLength = 0;
   if ((*newWord = malloc(10)) == NULL){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   if (scanChars(file, newWord, wordLength, isPrintable) == EOF)
      return EOF;
   return 0;
}

// Scans each of the characters of the given word
int scanChars(FILE *file, char **newWord, unsigned *wordLen, int *isPrintable){
   int mallocSize = 10;
   char ch;
   *wordLen = 0;
   while((fscanf(file, "%c", &ch)) != EOF){
      if (checkChar(newWord, wordLen, isPrintable, ch, &mallocSize) == 1)
         return 0;
   }
   *newWord = (char * ) realloc(*newWord, *wordLen);
   return EOF;
}

// Checks an individual character.
// Stops scanning a word when a space is found immediately after a nonspace (i.e. wordLen > 0).
int checkChar(char **newWord, unsigned *wordLen, int *isPrintable, char ch, int *mallocSize){
   if (isspace(ch) && *wordLen > 0){
      *newWord = (char * ) realloc(*newWord, *wordLen);
      return 1;
   }
   if (isspace(ch) && *wordLen == 0)
      return 0;

   checkNonSpace(newWord, wordLen, isPrintable, ch, mallocSize);

   return 0;
}

// Checks if character is printable, adds character to newWord, and mallocs more memory if needed.
void checkNonSpace(char **newWord, unsigned *wordLen, int *isPrintable, char ch, int *mallocSize){
   if (isprint(ch))
      *isPrintable = TRUE;
   (*newWord)[(*wordLen)++] = (char)tolower(ch);

   if (*wordLen >= *mallocSize){
      *mallocSize = 2*(*mallocSize);
      *newWord = (char * ) realloc(*newWord, *mallocSize);
   }

}

// Comparator function to be used in qsort.
// First tries comparing number of occurrences, then memcmp, and lastly the length of the words.
int compareWORD(const void *wordA, const void *wordB){
   const WORD *A = (WORD * )wordA;
   const WORD *B = (WORD * )wordB;
   if ((B->numOcc) - (A->numOcc) != 0)
      return ((B->numOcc) - (A->numOcc));
   if (A->len >= B->len){
      if (memcmp(A->name, B->name, B->len) != 0)
         return memcmp(A->name, B->name, B->len);
   }
   else if (memcmp(A->name, B->name, A->len) != 0)
      return memcmp(A->name, B->name, A->len);
   return ((A->len) - (B->len));
}
