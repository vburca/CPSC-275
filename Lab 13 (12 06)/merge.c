#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *mergestr(char* str1, char* str2) {
	char* str3;
	str3 =  (char*) malloc((strlen(str1) + strlen(str2) + 1) * sizeof(char));
	char* aux = str3;
	while (*str1 && *str2) {
		*aux = *str1;
		str1++;
		aux++;
		*aux = *str2;
		str2++;
		aux++;
	}
//	printf("str3 = %s\n", str3);
	while (*str2) {
		*aux = *str2;
		aux++;
		str2++;
	}	
	while (*str1) {
		*aux = *str1;
		aux++;
		str1++;
	}
	return str3;	
}


int main(int argc, char* argv[]) {

	if (argc == 3)
		printf("%s\n", mergestr(argv[1], argv[2]));
	else
		printf("Incorrect input\n");

	return 0;
}

