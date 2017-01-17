#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static volatile int isINT = 0;

void manejador (int s){
	if(s == SIGINT)
		isINT = 1;
}

int main(){

	sigset_t set, pending;
	struct sigaction sa;

	int rc = sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGTSTP);

	sigprocmask(SIG_BLOCK, &set, NULL);

	sleep(10);

	sigpending(&pending);

	if(sigismember(&pending, SIGINT))
		printf("%s\n", "Recibida señal SIGINT");
	else if(sigismember(&pending, SIGTSTP)){
		printf("%s\n", "Recibida señal SIGTSTP");
		sigprocmask(SIG_UNBLOCK, &set, NULL);
	}

	printf("%s\n", "Saliendo...");
	return 0;
}