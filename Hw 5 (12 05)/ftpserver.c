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

#include <sys/stat.h>
#include <fcntl.h>

#define mode S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH

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
	server_address.sin_port = htons(6992);

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

	char *filename;
	
	do {
		// read packet from client
		len = read(client_sockfd, buf, BUFSIZ);
		// send confirmation back - to be sure that 
		//	the contents of the buffer are synchronized
		write(client_sockfd, "ok", 3);
		if (strncmp(buf, "put", 3) == 0 ||
			strncmp(buf, "get", 3) == 0) {
			
			// -- PUT MODE -- 
			if (strncmp(buf, "put", 3) == 0) {
				char* filename = (char *) malloc((len - 4)*sizeof(char));
				strncpy(filename, buf + 4, len - 5);
				filename[len - 5] = '\0';
				char* header = "from_client_";
				char* new_filename;
				new_filename = (char *) malloc((1 + strlen(header) + strlen(filename)) * sizeof(char));
				// create the new filename
				strncpy(new_filename, header, strlen(header));
				new_filename[strlen(header)] = '\0';
				strncat(new_filename, filename, strlen(filename));
				// open the file with permissions
				int file = open(new_filename, O_CREAT|O_WRONLY, mode); 
				if (file < 0) // unable to open file
					write(STDOUT_FILENO, 
						"Error: Could not open file.\n",
						29);
				else {  	  // able to open file
					int n;	// length of packets from file
					char buf_file[BUFSIZ];	// buffer for file
					// read packet from client
					len = read(client_sockfd, buf, BUFSIZ);
					// while the next packet will be a packet from file 
					while (strncmp(buf, "fline", n) == 0) {
						// send confirmation back to client
						write(client_sockfd, "ok", 3);
						// read packet from file
						n = read(client_sockfd, buf_file, BUFSIZ);
						// write packet from file to file
						write(file, buf_file, n); 
						// send confirmation back
						write(client_sockfd, "ok", 3);
						// read packet from client
						len = read(client_sockfd, buf, BUFSIZ);
					}
					printf("Created file: %s  .\n", new_filename);
					close(file);	// close the file
				}
//				free(filename);
//				free(new_filename);
			}
			
			// -- GET MODE -- 
			else if (strncmp(buf, "get", 3) == 0) {
					char* filename =
						(char *) malloc((len - 4)*sizeof(char));
					strncpy(filename, buf + 4, len - 5);
					filename[len - 5] = '\0';
					int file = open(filename, O_RDONLY, 0);
					if (file >= 0) {	// able to open file
						// send confirmation back
						write(client_sockfd, "ok", 3);
						int n;	// length of packets from file
						char buf_file[BUFSIZ];	// buffer for file
						if ((len = read(client_sockfd, buf, BUFSIZ)) < 0)
							write(STDOUT_FILENO,
								"Error: No response from client.\n",
								33);
						// read packet from file
						while ((n = read(file, buf_file, BUFSIZ)) > 0) {
							// send client notification that packet from 
							//  file is coming
							write(client_sockfd, "fline", 6);
							// check for confirmation from client
							if ((len = read(client_sockfd, buf, BUFSIZ)) < 0)
								write(STDOUT_FILENO, 
									"Error: No response from client.\n",
									33);
							// send packet from file to client
							write(client_sockfd, buf_file, n);
							// check for confirmation from client
							if ((len = read(client_sockfd, buf, BUFSIZ)) < 0)
								write(STDOUT_FILENO,
									"Error: No response from client.\n",
									33);
						}
						write(client_sockfd, "ok", 3);
						close(file);	
					}
					else {
						write(STDOUT_FILENO, "Unable to open file.\n", 22);
						write(client_sockfd, "Unable to open file.\n", 22);
					}
//					free(filename);
				}
			
		}
	} while(strncmp(buf, "bye\n", len) != 0);
	close(client_sockfd);

}
