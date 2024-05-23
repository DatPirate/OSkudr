#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
void sigint_handler(int sig)
{
	printf("Aleksandrov(31) Caught SIGINT!\n");
	exit(0);
}

int main()
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		perror("signal error");
	pause();
	return 0;
}
