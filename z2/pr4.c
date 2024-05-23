#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int volatile count;
void handler(int sig) {
	printf("Aleksandrov(31) signal %d ouch that hurt \n", sig);
	count++;
}
int main (int argc, char **argv) {
	struct sigaction sa;
	int pid = getpid();
	printf("Aleksandrov(31) ok, let's go, kill me (%d) if you can! \n", pid);
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL)!=0){
		return(1);
	}
	while (count!=4){
	}
	printf("Aleksandrov(31) I've had enough! \n");
	return(0);
}
