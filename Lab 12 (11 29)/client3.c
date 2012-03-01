/*
 * Author: Vlad, Ryan
 * Date: 11/29/2011
 * File:
 *  client3.c - Internet domain, connection-based client
 *     Usage: client3 hostname_of_server
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
	server_address.sin_port = htons(6996);

	if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("generate error");
		exit(3);
	}

	if (connect(server_sockfd, (struct sockaddr *) &server_address, 
   	    sizeof(server_address)) < 0) {
		perror("connect error");
		exit(4);
	}
	int flag = 1;
	do {
		if (flag == 1) {
			write(STDOUT_FILENO, "> ", 3);
			if ((len=read(STDIN_FILENO, buf, BUFSIZ)) > 0)
				write(server_sockfd, buf, len);
			flag = 0;
		}
		else
		{
			if ((len=read(server_sockfd, buf, BUFSIZ)) > 0) 
				write(STDOUT_FILENO, buf, len);
			flag = 1;
		}
	} while (buf[0] != '.');
	close(server_sockfd);
	exit(0);
}

