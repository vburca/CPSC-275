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

#include <sys/stat.h>
#include <fcntl.h>

#define mode S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH

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
	server_address.sin_port = htons(6992);

	if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("generate error");
		exit(3);
	}

	if (connect(server_sockfd, (struct sockaddr *) &server_address, 
   	    sizeof(server_address)) < 0) {
		perror("connect error");
		exit(4);
	}

	do {
		write(STDOUT_FILENO, ">> ", 4);
		if ((len = read(STDIN_FILENO, buf, BUFSIZ)) > 0)
			// check for appropiate command sent to server
			
			// -- PUT MODE --
			if (strncmp(buf, "put", 3) == 0) {
				char* filename = 
						(char *) malloc((len - 4)*sizeof(char));
				strncpy(filename, buf + 4, len - 5);
				filename[len - 5] = '\0';
				int file = open(filename, O_RDONLY, 0);
				if (file >= 0) { // able to open file
					// send command and file information to server
					write(server_sockfd, buf, len);
					int n;	// length of packets from file	
					char buf_file[BUFSIZ];	// buffer for file
					// check for confirmation from server
					if ((len = read(server_sockfd, buf, BUFSIZ)) < 0)
						write(STDOUT_FILENO, 
							"Error: No response from server.\n",
							33);	
					// read packet from file	
					while ((n = read(file, buf_file, BUFSIZ)) > 0) {
						// send server notification that packet from file
						//  is coming	
						write(server_sockfd, "fline", 6);
						// check for confirmation from server
						if ((len = read(server_sockfd, buf, BUFSIZ)) < 0)
							write(STDOUT_FILENO,
								"Error: No response from server.\n",
								33);
						// send packet from file to server
						write(server_sockfd, buf_file, n);
						// check for confirmation from server
						if ((len = read(server_sockfd, buf, BUFSIZ)) < 0)
							write(STDOUT_FILENO,
								"Error: No response from server.\n",
								33);
					}
//					len = read(server_sockfd, buf, BUFSIZ);
//					write(STDOUT_FILENO, buf, len);
					write(server_sockfd, "ok", 3);
					close(file);
				}
				else		// unable to open file
					write(STDOUT_FILENO, "Error: Could not open file.\n", 29);
				free(filename);
			}


			// -- GET MODE --
			else if (strncmp(buf, "get", 3) == 0) {
					write(server_sockfd, buf, len);
					char* filename =
						(char *) malloc((len - 4)*sizeof(char));
					strncpy(filename, buf + 4, len - 5);
					filename[len - 5] = '\0';
					// get confirmation for receiving full command
					len = read(server_sockfd, buf, BUFSIZ);
					// get confirmation for opening file
					len = read(server_sockfd, buf, BUFSIZ);
					if (strncmp(buf, "ok", 3) == 0) {
						char* header = "from_server_";
						char* new_filename;
						new_filename = (char *) malloc((1 + strlen(header) + strlen(filename)) * sizeof(char));
						// create the new filename
						strncpy(new_filename, header, strlen(header));
						new_filename[strlen(header)] = '\0';
						strncat(new_filename, filename, strlen(filename));
						
						// open the file with permissions
						int file = open(new_filename, O_CREAT|O_WRONLY, mode);
						if (file < 0)	// unable to open file
							write(STDOUT_FILENO,
								"Error: Could not open file.\n",
								29);
						else {	// able to open file
							int n;	// length of packets from file
							char buf_file[BUFSIZ];	// buffer for file
							write(server_sockfd, "ok", 3);
							// read packet from server
							len = read(server_sockfd, buf, BUFSIZ);
							// while the next packet will be a packet from file
							while (strncmp(buf, "fline", len) == 0) {
								// send confirmation back to server
								write(server_sockfd, "ok", 3);
								// read packet from file
								n = read(server_sockfd, buf_file, BUFSIZ);
								// write packet from file to file
								write(file, buf_file, n);
								// send confirmation back
								write(server_sockfd, "ok", 3);
								// read packet from server
								len = read(server_sockfd, buf, BUFSIZ);
							}
						// client log to confirm creation of file
						write(STDOUT_FILENO, "Downloaded file.\n", 18);
						close(file);	// close the file
						}
					}
					else
						write(STDOUT_FILENO, buf, len);
					free(filename);
				}

			// -- EXIT MODE --
			else if (strncmp(buf, "bye\n", len) == 0)
					write(server_sockfd, buf, len);	

			else // wrong command
				printf(" Error: Unknown command. \n Known commands: put, get, bye.\n Usage: <command> <filename>\n");
	} while(strncmp(buf, "bye\n", len) != 0);
	close(server_sockfd);
	exit(0);
}

