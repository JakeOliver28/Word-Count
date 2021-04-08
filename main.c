#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "countwords.h"
#include "holdwords.h"

#define DEFAULT_NUM 10

int main(int argc, char *argv[]){
   WORD *words;
   int displayedWords, uniqueWords, totalWords, flags;
   flags = uniqueWords = totalWords = 0;

   // The number of words to be displayed is defaulted to 10
   displayedWords = DEFAULT_NUM;

   // Checks arguments given, counts words, sorts words by frequency, and prints results
   checkArgs(argc, argv, &displayedWords, &flags);
   countWords(argc, argv, &words, &uniqueWords, &totalWords, flags);
   qsort(words, uniqueWords, sizeof(WORD), compareWORD);
   printWords(words, displayedWords, uniqueWords, totalWords);

   free(words);
   return 0;
}
