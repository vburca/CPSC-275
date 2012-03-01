/*
	Author: Vlad Burca
	Date: 09-27-2011
	File: pb260.c
*/

#include <stdio.h>

/* We first create the byte that we need to add
	by shifting it to the right position. Then
	we check what position we have to put it in.
	If it is not at the edges of the word, we copy 
	the right-most bytes (until the desired adding
	position); then we add the desired byte in place
	and put back the copied bytes. In the other cases,
	in which the position is at the edges, we just 
	clear that space by shifting to left / right and
	then add the desired byte.
*/

unsigned replace_byte (unsigned x, int i, unsigned char b) {
	unsigned result, aux, byte;
	byte = (unsigned) b << (8 * i);
	if (i != 0 && i != (sizeof(unsigned) - 1)) {	
		unsigned aux;
		aux = (x << (8 * (4 - i))) >> (8 * (sizeof(unsigned) - i));
		x = (x >> (8 * (i + 1))) << (8 * (i + 1));
		result = x + byte + aux;
	} else if (i == 0) {
		x = (x >> 8) << 8;
		result = x + byte;
	} else if (i == (sizeof(unsigned) - 1)) {
		x = (x << 8) >> 8;
		result = x + byte;
	}
		
	return result;
}

int main() {
	unsigned x, b;
	int i;
	
	scanf("%x", &x);
	scanf("%d", &i);
	scanf("%x", &b);
	
	printf("\n Result = %#x \n", replace_byte(x, i, b));

	return 0;
}


