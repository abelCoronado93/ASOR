#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

static volatile int cont1 = 0;
static volatile int cont2 = 0;

void manejador(int s){
	if(s == SIGUSR1)
		printf("[PADRE] Petición tratada por hijo 1 (total: %i)\n", ++cont1);
	else if(s == SIGUSR2) printf("[PADRE] Petición tratada por hijo 2 (total: %i)\n", ++cont2);
}

int main(int argc, char ** argv){

	struct addrinfo hints, *res;
	struct sockaddr_storage cli;

	char buf[2];
	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];

	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = 0;

	getaddrinfo("::", argv[1], &hints, &res);

	int sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	bind(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

	freeaddrinfo(res);
	pid_t padre = getpid();
	pid_t hijo1 = fork();

	if(hijo1 != 0){
		pid_t hijo2 = fork();

		if(hijo2 != 0){
			struct sigaction act;
			act.sa_handler = manejador;
			act.sa_flags = SA_RESTART;
			sigaction(SIGUSR1, &act, NULL);
			sigaction(SIGUSR2, &act, NULL);
			
			while(wait(NULL)>0){}
			
			return 0;
		}
	}

	while(1){
		socklen_t clen = sizeof(cli);
		int bytes = recvfrom(sd, buf, 80, 0, (struct sockaddr *)&cli, &clen);
		buf[1] = '\0';
		getnameinfo((struct sockaddr *)&cli, clen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);

		if(hijo1 == 0){
			kill(padre, SIGUSR1);
			printf("[HIJO:%i,1] Host: %s Puerto: %s\n", getpid(), host, serv);
		} else {
			kill(padre, SIGUSR2);
			printf("[HIJO:%i,2] Host: %s Puerto: %s\n", getpid(), host, serv);
		}
		
		if(buf[0] == 'a'){
			sendto(sd, host, strlen(host), 0, (struct sockaddr *) &cli, clen);
		} else if(buf[0] == 'p'){
			sendto(sd, serv, strlen(serv), 0, (struct sockaddr *) &cli, clen);
		} else if(buf[0] == 'q'){
			sendto(sd, "exit", strlen("exit"), 0, (struct sockaddr *) &cli, clen);
			break;
		} else {
			sendto(sd, "comando no válido", strlen("comando no válido"), 0, (struct sockaddr *) &cli, clen);
		}
	}
	
	close(sd);
	return 0;

}