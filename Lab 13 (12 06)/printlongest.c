#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[]) {

	int i, imax;

	if (argc > 1) {	
		imax = 1;
		for (i = 2; i < argc; i++)
			if (strlen(argv[i]) > strlen(argv[imax]))
				imax = i;
		printf("%s\n", argv[imax]);
	}
	else
		printf("error: no arguments given\n");

	return 0;
}
