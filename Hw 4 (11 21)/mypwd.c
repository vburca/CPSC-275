/*
 * Author: Vlad Burca
 * Date: 11 - 21 - 2011
 * File: tree.c
 */

/*
 * NOTE: It is not working properly - can not go into some directories (maybe permission
 *				restrictions?)
 *
 */

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parse_dirs(DIR* dir, char* pathname) {
	if (dir != NULL) {					// check if directory can be opened
		struct dirent* entry;
		struct stat buf;

		short int found = 0;
		while ((entry = readdir(dir)) && found == 0) {	// read files from it
			if (strcmp(entry->d_name, "mypwd") == 0) {	// found execution file
				printf("%s \n", pathname);				// print path to this point
				found = 1;
			}
		}
		if (found == 0) {			// if not found, go deep into directories
			rewinddir(dir);			// refresh dir
			while (entry = readdir(dir)) {
				char* aux_path = (char*) malloc(1 + (strlen(pathname) + strlen(entry->d_name) + 1));
				strcat(aux_path, pathname);
				strcat(aux_path, "/");
				strcat(aux_path, entry->d_name);
					
				stat(aux_path, &buf);
				if (strcmp(entry->d_name, ".") != 0 &&
					strcmp(entry->d_name, "..") != 0) {		// ignore . and .. dirs
					if (S_ISDIR(buf.st_mode) == 1) {		// check if the file is a dir
						printf("%s \n", entry->d_name);
						parse_dirs(opendir(aux_path), aux_path);	
						// recursive call on the next dir
					}
				}
			}
		}
	}
}
					
		
	

int main() {
	
	char* pathname = "/";		// start at root

	//debug
	//printf("Directory to open: %s \n\n", pathname);
	
	DIR* dir = opendir(pathname);
	if (dir != NULL) {						// check if directory can be opened
		parse_dirs(dir, pathname);		// recursive call on the dir
	}
	else
		printf("Error - Can not open directory: %s \n", pathname); 	// error if dir can not be opened

	return 0;

}
		



