#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void sighandler(int signum) {
	printf("Aleksandrov(31) Caught signal %d, coming out...\n", signum);
	exit(1);
}
int main () {
	signal(SIGINT, sighandler);
	while(1);
	return(0);
}
