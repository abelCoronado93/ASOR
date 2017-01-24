#include <sched.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(){

	printf("%s\n", "----POR DEFECTO----");
	printf("Planificador: %i\n", sched_getscheduler(0));
	printf("Prioridad: %i\n", getpriority(PRIO_PROCESS, 0));
	printf("Prioridad máxima: %i\n", sched_get_priority_max(sched_getscheduler(0))); 
	printf("Prioridad mínima: %i\n", sched_get_priority_min(sched_getscheduler(0)));


	printf("%s\n", "---- CAMBIAMOS A PLANIFICADOR FIFO Y PRIORIDAD 12----");
	const struct sched_param p;
	sched_setscheduler(0, 0, &p);
	setpriority(PRIO_PROCESS, 0, 12); 
	printf("Planificador: %i\n", sched_getscheduler(0)); 
	printf("Prioridad: %i\n", getpriority(PRIO_PROCESS, 0)); 
	printf("Prioridad máxima: %i\n", sched_get_priority_max(sched_getscheduler(0)));
	printf("Prioridad mínima: %i\n", sched_get_priority_min(sched_getscheduler(0))); 

	
	return 0;
}

