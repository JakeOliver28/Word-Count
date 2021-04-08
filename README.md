# Word Count Project


## Purpose
This project counts the number of words in given files and prints the most commonly occurring words with their frequency.

## Usage
Use command "./a.out filename1.txt filename2.txt ..." to count the words in the files.  
If no filenames are given, the program will take input from stdin until an EOF is detected.  
Add "-n[X]" as an argument to change how many words are displayed. X is the desired number of words to be displayed. 10 is the default amount.

## Improvements
Improvements that could be made include:  
Words could be stored in a different data structure so that word lookup isn't significantly slowed down with a large amount of words.  
There are a lot of variables being passed around in different functions. Consolidating them into a struct could simplify data movement and improve readability.
