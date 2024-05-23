#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
void handler(int sig) {
	printf("Aleksandrov(31) signal %d was caught\n", sig);
	exit(1);
	return;
}
int not_so_good(){
	int x = 0;
	return 1 % x;
}
int main (int argc, char **argv) {
	struct sigaction sa;
	printf("Aleksandrov(31) Ok, let's go - I'll catch my own error.\n");
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	//and now we catch... FPE signals
	sigaction(SIGFPE, &sa, NULL);
	not_so_good();
	printf("Aleksandrov(31) Will probably not write this.\n");
	return(0);
}
