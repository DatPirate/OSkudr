#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void sighandler(int signum) {
	printf("Aleksandrov(31) Caught signal %d\n", signum);
	printf("Aleksandrov(31) Waiting a name...\n");
	alarm(5);
}
int main () {
	char s[80];
	signal(SIGALRM, sighandler);
	alarm(5);
	printf("Aleksandrov(31) Input a name ...\n");
	for(;;){
		printf("Aleksandrov(31) Name: ");
		if (fgets(s, sizeof(s), stdin) != NULL) break;
	}
	printf("Aleksandrov(31) OK! \n");
	return(0);
}
