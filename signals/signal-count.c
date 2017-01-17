#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static volatile int cont = 0;

void manejador (int s){
	cont++;
}

int main(){

	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);

	sa.sa_handler = manejador;
	sa.sa_flags = SA_RESTART;

	sigaction(SIGQUIT, &sa, NULL);

	while(cont < 3){
		sleep(1);
	}

	printf("%s\n", "Saliendo...");
	return 0;
}