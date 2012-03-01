/*
 * Author: Vlad Burca
 * Date: 12/03/2011
 * File:
 *  ftpclient.c - 
 *     Usage:
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct {
	int mode; 		// 0 - put, 1 - get, 2 - exit
	char* filename;	// striped filename
} ftp_details;

void main(int argc, char *argv[])
{
	char buf[BUFSIZ];
	int server_sockfd, len;
	struct sockaddr_in server_address;
	struct hostent *host;		/* the host (server) */

	if (argc != 2) {
		fprintf(stderr, "usage: %s server\n", argv[0]);
		exit(1);
	}
	host = gethostbyname(argv[1]);
	if (host == (struct hostent *) NULL) {
		perror("gethostbyname ");
		exit(2);
	}

	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	memcpy(&server_address.sin_addr, host->h_addr, host->h_length);
	server_address.sin_port = htons(6990);

	if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("generate error");
		exit(3);
	}

	if (connect(server_sockfd, (struct sockaddr *) &server_address, 
   	    sizeof(server_address)) < 0) {
		perror("connect error");
		exit(4);
	}
	
//	int flag = 1;
	ftp_details ftp_d;

	do {
		write(STDOUT_FILENO, ">> ", 4);
		if ((len = read(STDIN_FILENO, buf, BUFSIZ)) > 0)
			if (strncmp(buf, "put", 3) == 0) {	// check option put
				ftp_d.mode = 0;		// put mode
				ftp_d.filename =
					(char *) malloc((len - 4)*sizeof(char));
				// striped filename
				strncpy(ftp_d.filename, buf + 4, len - 5); 
				FILE* file = fopen(ftp_d.filename, "r");
				if (file) { 	// able to open file
					write(server_sockfd, &ftp_d, len);
					printf(" Reading from file: %s  .\n", ftp_d.filename);
					fclose(file);
				}
				else			// unable to open file
					printf(" Error: Could not open file: %s  .\n",
							ftp_d.filename);
			} 
			else if(strncmp(buf, "get", 3) == 0) { // check option get
				ftp_d.mode = 1;
				ftp_d.filename =
					(char *) malloc((len - 4)*sizeof(char));
				// striped filename
				strncpy(ftp_d.filename, buf + 4, len - 5);
				write(server_sockfd, &ftp_d, len);
				printf(" Reading from server file: %s  .\n", 
						ftp_d.filename);
			}
			else if(strncmp(buf, "bye\n", len) == 0) { // check exit option
				ftp_d.mode = 2;
				write(server_sockfd, &ftp_d, len);
			}
			else 			// unknown option
				printf(" Error: Unknown command.\n Known commands: put, get.\n Usage: <command> <filename>\n");
		} while(strncmp(buf, "bye\n", len) != 0);

	close(server_sockfd);
	exit(0);
}

