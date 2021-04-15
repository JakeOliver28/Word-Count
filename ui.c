#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "ui.h"

// Calls the helper function checkFlag for each of the arguments given
void checkArgs(int argc, char *argv[], int *numWords, int *flags){
   int i;
   for (i = 1; i < argc; i++){
      checkFlag(argv, numWords, i, flags);
   }
}

// Checks whether a given argument is a flag and whether it is the proper format
void checkFlag(char *argv[], int *numWords, int i, int *flags){
   if ((argv[i][0] == '-') && (argv[i][1] == 'n')){
      scanNum(argv, numWords, i);
      (*flags)++;
   }
   else if (argv[i][0] == '-'){
      fprintf(stderr, "Usage: wf [-nX] [file...]\n");
      exit(EXIT_FAILURE);
   }
}

// Scans the flagged number and updates the number of words to display
void scanNum(char *argv[], int *numWords, int i){
   if (sscanf(((argv[i]) + 2), "%d", numWords) == 0){
      fprintf(stderr, "Usage: wf [-nX] [file...]\n");
      exit(EXIT_FAILURE);
   }
   if (*numWords == 0){
      fprintf(stderr, "Usage: wf [-nX] [file...]\n");
      exit(EXIT_FAILURE);
   }
}

// Prints all the words to be displayed
void printWords(WORD *words, int numWords, int uniqueWords, int totalWords){
   int i;
   printf("%d unique words found in %d total words\n", uniqueWords, totalWords);
   for (i = 0; i < numWords && i < uniqueWords; i++){
      printSingleWord(words, numWords, i);
   }
}

// Prints a single word with its total number of occurrences
void printSingleWord(WORD *words, int numWords, int i){
   int j;
   printf("%10d - ", (words[i]).numOcc);
   for (j = 0; j < (words[i]).len && j < 30; j++){
      if (isprint(((words[i]).name)[j]))
         printf("%c", ((words[i]).name)[j]);
      else
         printf("%c", UCHAR_MAX);
   }

   if ((words[i]).len > 30)
      printf("...");
   printf("\n");
}
