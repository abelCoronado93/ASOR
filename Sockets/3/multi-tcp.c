/*Author: Abel Coronado*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv){

	struct addrinfo hints;
	hints.ai_flags = AI_PASSIVE; //Devolver 0.0.0.0 ::
	hints.ai_family = AF_UNSPEC; // IPv4 ó IPV6
	hints.ai_socktype = SOCK_STREAM; //TCP
	memset(&hints, 0, sizeof(struct addrinfo));

	struct addrinfo * result;
	int rc = getaddrinfo(argv[1], argv[2], &hints, &result);

	int sd = socket(result->ai_family, result->ai_socktype, 0);

	bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);

	freeaddrinfo(result);

	struct sockaddr_storage cliente;
	socklen_t cliente_len = sizeof(cliente);
	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];
	char buffer[256];
	ssize_t bytes;
	int cliente_sd;

	listen(sd, 5);

	while (1) {
		cliente_sd = accept(sd, (struct sockaddr *) &cliente, &cliente_len);
		getnameinfo((struct sockaddr *) &cliente, cliente_len, host,
				NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
		
		printf("Conexión desde Host:%s Puerto:%s\n", host, serv);
		
		pid_t pid = fork();

		if(pid == 0){

			close(sd);

			while(1){

				bytes = recv(cliente_sd, buffer, 255, 0);
				buffer[bytes] = '\0';
				printf("Red %i: %s\n", getpid(), buffer);
				if((buffer[0] == 'Q') && (bytes == 2)){
					printf("%s\n", "Conexión terminada...");
					break;
				}
				send(cliente_sd, buffer, bytes, 0);
			}
			close(cliente_sd);
			return 0;
		}
		else {
			close(cliente_sd);
		}
	}
return 0;
}