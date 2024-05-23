#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
int volatile done = 0;
void handler(int sig, siginfo_t *siginfo, void *context) {
	printf("Aleksandrov(31) signal %d was caught\n", sig);
	printf("Aleksandrov(31) your UID is %d\n", siginfo->si_uid);
	printf("Aleksandrov(31) your PID is %d\n", siginfo->si_pid);
	done = 1;
}
int main (int argc, char **argv) {
	int pid = getpid();
	printf("Aleksandrov(31) Ok, let's go - kill me (%d) and I'll tell you who you are.\n", pid);
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigaction(SIGINT, &sa, NULL)!=0){
		return(1);
	}
	while(!done){
	}
	printf("Aleksandrov(31) Told you so!\n");
	return(0);
}
