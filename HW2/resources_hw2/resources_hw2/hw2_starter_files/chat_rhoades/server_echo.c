#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>
#include <sys/types.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

#define STRLEN 120

struct sockaddr_in server_addr, client_addr;
uint16_t server_port;


void usage() 
{
	printf("Command format: ./server port_number\n\n");
	printf("\tport_number \tshould be a well-known port\n\n");
	exit(EXIT_FAILURE);
}


int main(int argc, char *argv[])
{
	int sockfd, nsockfd;
	time_t ticks;
	socklen_t client_len;
	char t[256];


	if(argc == 1)
	{
		printf("Server port number missing!\n");
		usage();
	}

	server_port = atoi(argv[1]);
	ticks = time(NULL);
	printf("\nServer starts running at %s\n",(char *) ctime(&ticks));


	// create a socket on the server ent
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		fprintf(stderr,"\nError openning socket!\n");
		exit(EXIT_FAILURE);
	}

	bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);	// big-endian conversion
	server_addr.sin_port = htons(server_port);	

	if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
	{
		fprintf(stderr, "\nError binding address to socket\n");
		exit(EXIT_FAILURE);
	}

	// listen to client connection
	if(listen(sockfd, 1) < 0)
	{
		fprintf(stderr,"\nError creating a passive connection\n");
		exit(EXIT_FAILURE);
	}

	for( ; ; )
	{
		client_len = sizeof(client_addr);
		if((nsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_len)) < 0)
		{
			fprintf(stderr, "\nError accepting client call!\n");
			exit(EXIT_FAILURE);
		}

		char buffer[STRLEN + 1];
		int n;
		int server_quit = 0;
		while(1) {
			bzero(buffer, sizeof(buffer));
			n = read(nsockfd, buffer, STRLEN);
			if(n <= 0) {
				printf("client fail\n");
				break;
			}

			//get client message
			buffer[n] = '\0';

			ticks = time(NULL);
			strncpy(t, ctime(&ticks), sizeof(t));
			t[strlen(t) - 1] = '\0';
			printf("Client[%s]:$ %s\n", t, buffer);

			if(strcmp(buffer, "quit") == 0) {
				printf("client closed\n");
				break;
			}

			//send server message
			ticks = time(NULL);
			strncpy(t, ctime(&ticks), sizeof(t));
			t[strlen(t) - 1] = '\0';
			printf("Server[%s]:$ ", t);
			fflush(stdout);

			bzero(buffer, sizeof(buffer));
			if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
				strncpy(buffer, "quit", sizeof(buffer));
			}
			buffer[strcspn(buffer, "\n")] = '\0';
			

			//fail checks
			if (write(nsockfd, buffer, strlen(buffer)) < 0) {
				perror("brokey");
				break;
			}

			if (strcmp(buffer, "quit") == 0) {
				server_quit = 1;
				break;
			}
		}

	close(nsockfd);
	if(server_quit) {
		break;

	}
}
	close(sockfd);
	return 0;
} // end of main


