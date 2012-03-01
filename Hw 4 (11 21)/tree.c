/*
 * Author: Vlad Burca
 * Date: 11 - 21 - 2011
 * File: tree.c
 */

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parse_dirs(DIR* dir, char* pathname, int tabs) {
	if (dir != NULL) {					// check if directory can be opened
		struct dirent* entry;
		struct stat buf;
		char* tab = "  ";
		
		while (entry = readdir(dir)) {	// read files from it
			// dinamically allocate enough space for the path of the current file
//			char* aux_path = (char*) malloc(1 + (strlen(pathname) + strlen(entry->d_name) + 1));
			char* aux_path = (char*) malloc(1024);
			strcat(aux_path, pathname);
			strcat(aux_path, "/");
			strcat(aux_path, entry->d_name);
			// created the current file path
			
			stat(aux_path, &buf);
			if (strcmp(entry->d_name, ".") != 0 &&
				strcmp(entry->d_name, "..") != 0) {		// ignore . and .. dirs
				if (S_ISDIR(buf.st_mode) == 1) {		// check if the file is a dir
					int i;
					for (i = 0; i < tabs; i++)			// print the tabbing
						printf("%s", tab);
					printf("%s \n", entry->d_name);		// print the name of the dir
					parse_dirs(opendir(aux_path), aux_path, tabs + 1);	
					// recursive call on the next dir
				}
			}
		}
	}
//	else
//		printf("Could not open directory! \n");
}
					
		
	

int main(int argc, char* argv[]) {
	
	char* pathname = ".";

	if (argc > 1)
		pathname = argv[1];

	//debug
	//printf("Directory to open: %s \n\n", pathname);
	
	DIR* dir = opendir(pathname);
	if (dir != NULL) {						// check if directory can be opened
		printf("%s \n", pathname);			// print the first directory
		parse_dirs(dir, pathname, 1);		// recursive call on the dir
	}
	else
		printf("Error - Can not open directory: %s \n", pathname); 	// error if dir can not be opened

	return 0;

}
		



