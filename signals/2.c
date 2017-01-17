/*Escribir un programa que instale un manejador sencillo para las señales SIGINT y SIGTSTP.
El manejador debe contar las veces que ha recibido la señal. El programa principal permanecerá en un
bucle que se detendrá cuando se hayan recibido 10 señales. El número de señales de cada tipo se
mostrará al finalizar el programa.*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static volatile int contINT = 0;
static volatile int contTSTP = 0;

void manejador (int s){
	if(s == SIGINT)
		contINT++;
	else if(s == SIGTSTP)
		contTSTP++;
}

int main(){

	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGTSTP);

	sa.sa_handler = manejador;
	sa.sa_flags = SA_RESTART;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);

	while((contINT + contTSTP) < 10){
		
	}

	printf("\n%s: %i\n", "Señales SIGINT recibidas", contINT);
	printf("%s: %i\n", "Señales SIGTSTP recibidas", contTSTP);

	return 0;
}