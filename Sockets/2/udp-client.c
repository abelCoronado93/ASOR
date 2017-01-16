 /*Author: Abel Coronado*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char ** argv){

	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM; //PROTOCOLO UDP

	struct addrinfo * res;

	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

	if(rc != 0){
		printf("Error getaddrinfo(): %s\n", gai_strerror(rc));
		return -1;
	}

	int cliente = socket(res->ai_family, 
		res->ai_socktype, res->ai_protocol);
	
	char buf[2];
	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];	

	struct sockaddr_storage cli;
	socklen_t clilen = sizeof(cli);

	while(1){
		
		scanf("%s", buf);
		buf[1] = '\0';
		ssize_t send = sendto(cliente, buf, 2, 0, 
			res->ai_addr, res->ai_addrlen);

		char s[50];
		ssize_t bytes = recvfrom(cliente, s, 50, 0, (struct sockaddr *) &cli, &clilen);

		getnameinfo((struct sockaddr *) &cli, clilen, host,
		NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

		printf("Recibí %ld byte(s) de %s(%s)\n", bytes, host, serv);
		printf("/tMensaje: %s\n", s);

	}
	
	return 0;
}
