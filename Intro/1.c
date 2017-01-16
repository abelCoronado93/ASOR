#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main()
{

    int errno;
	int rc;
	/* CNote:  there  are cases where setuid() can fail even when the caller is
       UID 0; it is a grave security error to  omit  checking  for  a  failure
       return from setuid().
	*/
	rc = setuid(0);
	if(rc == -1){
		perror("Error setuid()");
		perror(errno);
	}
	return 1;
}
