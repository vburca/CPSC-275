/*
 * Author: Vlad Burca, Greg Vaughan
 * Date: 11 - 15 - 2011
 * File: myls.c
 */

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int main() {
	
	DIR* dir = opendir((const char*)".");
	struct dirent* entry;
	struct stat buf;
	int closed;
	struct passwd* usrid;
	struct group* grpid; 
	time_t time;
	
	int i;
	char* date;
	char filetype[2] = "-d";
	char usr[4] = "---\0";
	char grp[4] = "---\0";
	char oth[4] = "---\0";


	if (dir != NULL) {
		while (entry = readdir(dir)) {
			stat(entry->d_name, &buf);
			
			if (buf.st_mode & S_IRUSR)
				usr[0] = 'r';
			if (buf.st_mode & S_IWUSR)
				usr[1] = 'w';
			if (buf.st_mode & S_IXUSR)
				usr[2] = 'x';
			if (buf.st_mode & S_IRGRP)
				grp[0] = 'r';
			if (buf.st_mode & S_IWGRP)
				grp[1] = 'w';
			if (buf.st_mode & S_IXGRP)
				grp[2] = 'x';
			if (buf.st_mode & S_IROTH)
				oth[0] = 'r';
			if (buf.st_mode & S_IWOTH)
				oth[1] = 'w';
			if (buf.st_mode & S_IXOTH)
				oth[2] = 'x';
		
			usrid = getpwuid(buf.st_uid);
			grpid = getgrgid(buf.st_gid);
			time = buf.st_mtime;
			date = ctime(&time);
			date[strlen(date) - 1] = '\0';		
			
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)	
				printf("%c | %s | %s | %s | %d |  %s %s  | %d | %s | %s \n", 
						filetype[S_ISDIR(buf.st_mode)], 
						usr,
						grp,
						oth,
						buf.st_nlink,
						usrid->pw_name,
						grpid->gr_name,
						(int) buf.st_size,
						date,
						entry->d_name
						);
		}

		closed = closedir(dir);
	
	}

	return 0;

}
		



