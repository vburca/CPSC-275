/*
 * Author: Vlad Burca
 * Date: 12/03/2011
 * File: 
 *  ftpserver.c - 
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
	int mode;
	char* filename;
} ftp_details;

void main(void)
{
	char buf[BUFSIZ];
	int server_sockfd, client_sockfd, client_len;
	struct sockaddr_in client_address, server_address;
	int len, i;

	if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("generate error");
		exit(1);
	}
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(6990);

	if (bind(server_sockfd, (struct sockaddr *) &server_address, 
	    sizeof(server_address)) < 0) {
		perror("bind error");
		close(server_sockfd);
		exit(2);
	}
	if (listen(server_sockfd, 5) < 0) {
		perror("listen error");
		exit(3);
	}
	client_len = sizeof(client_address);
	if ((client_sockfd = accept(server_sockfd, 
	    (struct sockaddr *) &client_address, &client_len)) < 0) {
		perror("accept error");
		close(server_sockfd);
		exit(4);
	}

//	int flag = 0;
//	char *filename;
//	char *aux;

	ftp_details ftp_d;
	ftp_d.filename = (char *) malloc(32000 * sizeof(char));
	
	do {
		len = read(client_sockfd, &ftp_d, BUFSIZ);

		printf("Hello!\n");
		switch (ftp_d.mode) {
			case 0: printf("PUT %s  .\n",  ftp_d.filename); break;
			case 1: printf("GET %s  .\n",  ftp_d.filename); break;
			case 2: printf("EXIT MODE \n"); break;
		}
	} while (ftp_d.mode != 2);	
	
/*		if (flag == 0) {
			len = read(client_sockfd, buf, BUFSIZ);
			write(STDOUT_FILENO, buf, len);
			// aux variable for stripping the new line char
			aux = (char *) malloc((len - 4)*sizeof(char));
			// stripped the new line char
			strncpy(aux, buf + 4, len - 5);
			filename = (char *) malloc(12 + strlen(aux)*sizeof(char));
			// creating the name of the file
			printf("\n Aux = %s.", aux);
			strcpy(filename, "from_client_");
			strncat(filename, aux, strlen(aux) - 1);
//			sprintf(filename, "from_client_%s", aux);
			if (strncmp(buf, "put", 3) == 0) {
				FILE* file = fopen(filename, "w");
				// write to the file
				fprintf(file, "TEST\n");
				printf("Created file: %s \n", filename);
				fclose(file);	// close the file
			}
			else if (strncmp(buf, "get", 3) == 0) {
					FILE* file = fopen(filename, "r");
					if (file) { // able to open file
						printf("Reading from file.\n");
						fclose(file);
					}
					else
						printf(" Error: Could not open file: %s .\n",
									filename);
				}

//			flag = 1;
		}
		else
		{ 
			write(STDOUT_FILENO, "> ", 3);
			if ((len = read(STDIN_FILENO, buf, BUFSIZ)) > 0)
				write(client_sockfd, buf, len);
			flag = 0;
		}
	} while(strcmp(buf, "bye\n") != 0);
*/	close(client_sockfd);
}

