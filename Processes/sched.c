#include <sched.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(){

	printf("%s\n", "----POR DEFECTO----");
	printf("Planificador: %i\n", sched_getscheduler(0)); //Saco el planificador por defecto (0:OTHER, 1:FIFO, 2:RR)
	printf("Prioridad: %i\n", getpriority(PRIO_PROCESS, 0));
	printf("Prioridad máxima: %i\n", sched_get_priority_max(sched_getscheduler(0))); //0
	printf("Prioridad mínima: %i\n", sched_get_priority_min(sched_getscheduler(0))); //0


	printf("%s\n", "---- CAMBIAMOS A PLANIFICADOR FIFO Y PRIORIDAD 12----");
	const struct sched_param p;
	sched_setscheduler(0, 0, &p);
	setpriority(PRIO_PROCESS, 0, 12); 
	printf("Planificador: %i\n", sched_getscheduler(0)); //DEVUELVE 0, NO CAMBIA EL PLANIFICADOR
	printf("Prioridad: %i\n", getpriority(PRIO_PROCESS, 0)); //DEVUELVE 12 (BIEN)
	printf("Prioridad máxima: %i\n", sched_get_priority_max(sched_getscheduler(0))); //Siempre sale 0
	printf("Prioridad mínima: %i\n", sched_get_priority_min(sched_getscheduler(0))); //Siempre sale 0

	
	return 0;
}

