/* 
	Author: Vlad Burca
	Date: 09-27-2011
	File: pb271.c
*/   

/* 
	A. The problem with the previous implementation
		of the given function is that it does not
		extend the sign for the extracted bit, when
		it converts it into a 32-bit integer. 
	   For example, if word = 0x000080FF and
		bytenum = 1, the result will be 128, even
		though the most significant bit of the
		byte indexed 1 is 1 and should be extended
		for the 32-bit integer representation, 
		therefore giving the correct value: -128.
*/


#include <stdio.h>

/*
int bad_xbyte(unsigned word, int bytenum) {
	
	return (word >> (bytenum << 3)) & 0xFF;

}
*/

/*
B. Correct implementation of xbyte.
*/
int xbyte(unsigned word, int bytenum) {
	/* The following implementation takes care of extending
		the most significant bit of the extracted byte.
		In order to do so, we have to shift the desired
		byte in the position of the most significant one.
		We do this by shifting the word to the left for
		how many bits are left to the left of the desired
		byte. After that, we have to cast the result into
		an int so that the compiler knows to apply the
		arithmetic right shift. Now we right shift 
		(arithmetic) for 24 bits so that the extracted
		byte will be in the least significant position.
		Therefore, we extracted the desired byte and we
		also extended its sign bit with the proper value.
	*/ 

	return ((int)(word << (24 - (bytenum << 3)))) >> 24;

}


int main () {

	unsigned word;
	int bytenum;

	printf(" word = ");
	scanf("%x", &word);
	printf(" bytenum = ");
	scanf("%d", &bytenum);
	
	printf("\n RESULT: %d \n", xbyte(word, bytenum));	

	return 0;
}
