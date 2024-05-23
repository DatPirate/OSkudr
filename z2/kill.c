#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
int main()
{
	pid_t pid;
	if ((pid = fork()) == 0) {
		pause();
		printf("Aleksandrov(31) control should never reach here!\n");
		exit(0);
	}
	kill(pid, SIGKILL);
	exit(0);
}
