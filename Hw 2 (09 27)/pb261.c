/*
	Author: Vlad Burca
	Date: 09-27-2011
	File: pb261.c
*/

#include <stdio.h>


int a(int x) {
	/* Check if any of the bits of x equals 1
		with bitwise AND on -1 (binary all 1s).
		If there is at least one bit equal to 1, 
		this will return the binary representation
		of a number != 0 which, applied logical AND
		to it with 1 will return 1, or 0 if the 
		number = 0.
	*/
	return (x && 1);
}

int b(int x) {
	/* By applying the bit negation on x, we 
		transform all the 0's into 1's, so we can now 
		do the same operation as in function a().
	*/
	return (~x && 1);
}

int c(int x) {
	/* We extract the LSB, by applying the bitwise 
		AND on x with 0xFF (all 0's except for the
		LSB byte, which is all 1's - therefore, the
		operation is preserving the LSB byte from x).
		Now we apply the a() function on this byte.
	*/
	// printf("\n LSB: %#x \n", x & 0xFF);
	return a(x & 0xFF);
}

int d(int x) {
	/* We extract the MSB, by bit shifting x to the
		right with the corresponding number of bytes
		(given by the sizeof function minus one, since
		we don't want to get rid of the MSB of x. As in
		c(), we apply bitwise AND to get all 0's but the
		MSB (which is now in the position of LSB). 
		Now, since we have all those extra 0's that will
		influence the result of the operation on the desired
		byte, we have to add a "bias", which is all 1's but
		the last bit. Therefore, the final result will look
		like all 1's but the last byte (MSB of x, which is
		in the LSB case after all the formatting). Passing
		this result to b(), we will get the desired result. 
	*/ 
	// printf("\n MSB: %#x \n", (x >> ((sizeof(int) - 1) << 3)) & 0xFF);
	return b((( x >> ((sizeof(int) - 1) << 3)) & 0xFF) + (-1 ^ 0xFF));
}


int main() {
	int x;
	
	printf(" x = ");
	scanf("%x", &x);
	
	// printf("x = %#x \n", x);
	
	printf(" A: %d \n", a(x));
	printf(" B: %d \n", b(x));
	printf(" C: %d \n", c(x));
	printf(" D: %d \n", d(x));	

	return 0;
}	
