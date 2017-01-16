/*Author: Abel Coronado*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char ** argv){

	struct addrinfo hints;
	hints.ai_flags = AI_PASSIVE; //Devolver 0.0.0.0 ::
	hints.ai_family = AF_UNSPEC; // IPv4 ó IPV6
	hints.ai_socktype = SOCK_STREAM; //TCP
	memset(&hints, 0, sizeof(struct addrinfo));

	struct addrinfo * result;
	int rc = getaddrinfo(argv[1], argv[2], &hints, &result);

	int sd = socket(result->ai_family, result->ai_socktype, 0);
	

	struct sockaddr_storage server;
	socklen_t server_len = sizeof(server);

	connect(sd, (struct sockaddr *) result->ai_addr, 
		result->ai_addrlen);

	freeaddrinfo(result);
	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];

	getnameinfo((struct sockaddr *) &server, server_len, host,
				NI_MAXHOST, serv, NI_MAXSERV, 
				NI_NUMERICHOST|NI_NUMERICSERV);

	char bufSalida[256];
	char bufEntrada[256];

	printf("Conexión a Host:%s Puerto:%s\n", host, serv);

	while (1) {

		ssize_t bytesSalida = read(0, bufSalida, 255);
		bufSalida[bytesSalida]= '\0';

		send(sd, bufSalida, bytesSalida, 0);

		ssize_t bytesEntrada = recv(sd, bufEntrada, 255, 0);
		bufEntrada[bytesEntrada] = '\0';
		
		printf("%s\n", bufEntrada);
	}

	close(sd);
	
return 0;
}