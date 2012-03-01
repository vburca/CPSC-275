/*
Authors: Vlad Burca; Alex Zhang
Filename: palindrome.c
Date: 09/20/2011
*/

#include <stdio.h>
#include <string.h>

int main() {

	char word[50];
	int i, palindrome;
	
	while (scanf("%s", word) != EOF) {
		if (strlen(word) == 7) {
			palindrome = 1;
			for (i = 0; (i <= strlen(word) / 2) && (palindrome == 1); i++)
				if (word[i] != word[strlen(word) - 1 - i])
					palindrome = 0;
			if (palindrome)
				printf("%s \n", word);
		}
	}
	return 0;
}
