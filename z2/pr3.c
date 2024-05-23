#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int volatile count;
void handler(int sig) {
	printf("Aleksandrov(31) signal %d ouch that hurt \n", sig);
	count++;
}
int main (int argc, char **argv) {
	int pid = getpid();
	printf("Aleksandrov(31) ok, let's go, kill me (%d) if you can! \n", pid);
	struct sigaction sa;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	while (count!=4){
		kill(pid, SIGINT);
	}
	printf("Aleksandrov(31) I've had enough! \n");
	return(0);
}
