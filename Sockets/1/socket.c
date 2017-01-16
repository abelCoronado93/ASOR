/*Author: Abel Coronado*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv){

	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;

	struct addrinfo * res;

	int rc = getaddrinfo(argv[1], NULL, &hints, &res);

	if(rc != 0){
		printf("Error getaddrinfo(): %s\n", gai_strerror(rc));
		return -1;
	}

	printf("%s\n", "El protocolo 2 es AF_INET | El protocolo 10 es AF-INET6");
	printf("%s\n", "El protocolos 1,2,3 corresponden a SOCK_STREAM, SOCK_DGRAM y SOCK_RAW, respectivamente");

	struct addrinfo *tmp;
	for(tmp = res; tmp != NULL; tmp = tmp->ai_next){
		char host[NI_MAXHOST];
		getnameinfo(tmp->ai_addr, tmp->ai_addrlen, host, 
			NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

		printf("%s ", host);
		printf("%i ", tmp->ai_family);
		printf("%i\n", tmp->ai_socktype);
	}

	freeaddrinfo(res);

	return 0;
}
