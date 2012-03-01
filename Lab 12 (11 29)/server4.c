/* 
 *  server4.c - UNIX domain, connectionless server
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_FILE "server_socket"

main(void)
{
	int orig_sock, clnt_len, i;
	static struct sockaddr_un clnt_adr, serv_adr;
	static char buf[10];
	void clean_up(int, char *);
	
	if ((orig_sock = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) {
		perror("generate error");
		exit(1);
	}
	
	serv_adr.sun_family = AF_UNIX;
	strcpy(serv_adr.sun_path, SERVER_FILE);
	unlink(SERVER_FILE);
	
	if (bind(orig_sock, (struct sockaddr *) &serv_adr, 
          sizeof(serv_adr.sun_family) + strlen(serv_adr.sun_path)) < 0) {
		perror("bind error");
		clean_up(orig_sock, SERVER_FILE);
		exit(2);
	}

	for (i = 1; i <= 10; i++) {
		recvfrom(orig_sock, buf, sizeof(buf), 0, (struct sockaddr *) 
                     &clnt_adr, &clnt_len);
		printf("s-> %s", buf);
	}
	clean_up(orig_sock, SERVER_FILE);
	exit(0);
}

void clean_up(int sd, char *file)
{
	close(sd);
	unlink(file);
}

