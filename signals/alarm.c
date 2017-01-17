#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static volatile int alarM = 0;

void manejador(int s){
	alarM = 1;
}

int main(int argc, char ** argv){

	int secs = atoi(argv[1]);
	alarm(secs);
	printf("%i\n", getpid());

	sigset_t set, pending;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);

	sigprocmask(SIG_BLOCK, &set, NULL);

	struct sigaction sa;
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = manejador;
	sigaction(SIGALRM, &sa, NULL);

	while(alarM == 0){

	}

	sigpending(&pending);

	if(sigismember(&pending, SIGUSR1))
		printf("%s\n", "Borrado cancelado.");

	else {
		printf("%s\n", "Ejecutable borrado.");
		system("rm alarm");
	}
	
	return 0;
}