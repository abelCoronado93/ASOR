#include <string.h>
#include <stdio.h>

int main()
{
	for(int i = 0; i<255; i++)
		printf("Error %i: %s \n", i, strerror(i));
return 0;
}
