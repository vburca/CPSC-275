/*
 * Author: Vlad, Ryan
 * Date: 11/29/2011
 * File:
 *  server3.c - Internet domain, connection-based server
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
	server_address.sin_port = htons(6997);

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
	int flag = 0;
	do {
		if (flag == 0) {
			len = read(client_sockfd, buf, BUFSIZ);
			write(STDOUT_FILENO, buf, len);
			flag = 1;
		}
		else
		{ 
			write(STDOUT_FILENO, "> ", 3);
			if ((len = read(STDIN_FILENO, buf, BUFSIZ)) > 0)
				write(client_sockfd, buf, len);
			flag = 0;
		}
//		if (buf[0] == '.')
//			break;
	} while(buf[0] != '.');
	close(client_sockfd);
}

