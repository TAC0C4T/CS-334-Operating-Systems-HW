#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define STRLEN 120

struct sockaddr_in server_addr;
uint16_t server_port;

void usage()
{
	fprintf(stderr, "Command format: ./client port_number server_ip\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	int sockfd;
	time_t ticks;
	int n, bytes_to_read;
	char *buff, buffer[STRLEN+1];

	if (argc < 3) 
	{
		printf("IP address or port number is missing!\n");
		usage();
	}

	server_port = atoi(argv[1]);
	ticks = time(NULL);
	printf("\nClient process starts at %s\n", (char *) ctime(&ticks));

	// create a socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "\nError openning socket!\n");
		exit(EXIT_FAILURE);
	}

	bzero((char *) &server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[2]);    // takes the dotted decimal IP address and convert it to 32-bit IP address in big-endian format
	server_addr.sin_port = htons(server_port);	// convert the port number in big endian format

	// connect to the remote server
	if(connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
	{
		fprintf(stderr, "\nError connecting to the server\n");
		exit(EXIT_FAILURE);
	}

	printf("Communicating with the server...\n");
	printf("Server time is ");

	// reading from the socket
	buff = buffer;
	bytes_to_read = STRLEN+1;
	while((n = read(sockfd, buff, bytes_to_read)) > 0)
	{
		buff += n;
		bytes_to_read -= n;
	}
	printf("%s\n\n",buffer);

	close(sockfd);

	return 0;
}
