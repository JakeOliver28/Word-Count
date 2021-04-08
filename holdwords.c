#include <stdio.h>
#include <stdlib.h>
#include "holdwords.h"
#include "countwords.h"

#define FALSE 0
#define TRUE 1

// Attempts to add the new word to the list of words.
// Checks if word is printable and calls helper function.
void addWord(WORD **words, char *newWord, unsigned wordLen, int isPrintable, int *mallocSize, int *uniqueWords, int *totalWords){
   if (isPrintable){
      (*totalWords)++;
      addPrintableWord(words, newWord, wordLen, mallocSize, uniqueWords);
   }
}

// Attempts to add the printable word to the list of words
void addPrintableWord(WORD **words, char *newWord, unsigned wordLen, int *mallocSize, int *uniqueWords){
   int i, isDiffWord;
   isDiffWord = TRUE;
   // Iterate through currently stored words and check for equality
   for (i = 0; i < (*uniqueWords); i++){
      if (isSameWord((*words)[i], newWord, wordLen) == TRUE){
         isDiffWord = FALSE;
         ((*words)[i]).numOcc++;
         break;
      }
   }
   if (isDiffWord)
      addNewWord(words, newWord, wordLen, mallocSize, uniqueWords, i);
}

// Checks if the word from the list is the same as the new word
int isSameWord(WORD listWord, char *newWord, unsigned wordLength){
   int i;
   if (listWord.len != wordLength)
      return FALSE;
   for (i = 0; i < listWord.len; i++){
      if ((listWord.name)[i] != newWord[i])
         return FALSE;
   }
   return TRUE;
}

// Adds new word to list and mallocs more space if necessary
void addNewWord(WORD **words, char *newWord, unsigned wordLen, int *mallocSize, int *uniqueWords, int i){
   ((*words)[i]).name = newWord;
   ((*words)[i]).numOcc = 1;
   ((*words)[i]).len = wordLen;
   (*uniqueWords)++;
   if (*uniqueWords >= *mallocSize){
      *mallocSize = (*mallocSize) * 2;
      *words = (WORD * ) realloc(*words, (*mallocSize) * sizeof(WORD));
   }
}
