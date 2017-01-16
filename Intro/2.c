#include <string.h>
#include <stdio.h>

int main()
{
	int i;

	for(i = 0; i<255; i++){
		printf("Error %i: %s \n", i, strerror(i));

	}
    
	return 1;
}
