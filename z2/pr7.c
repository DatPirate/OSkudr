#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
void sighandler(int sign) {
	printf("Aleksandrov(31) Caught signal %d: waiting...\n", sign);
	signal (SIGALRM, sighandler);
}
int main () {
	char s[80];
	int pid;
	signal(SIGALRM, sighandler);
	if (pid=fork()) { //parent
		for(;;){
			sleep(5);
			kill(pid, SIGALRM); //to child
		}
	}
	else{//child
		printf("Aleksandrov(31) Input a name ...\n");
		for(;;){
			printf("Aleksandrov(31) Name: ");
			if (fgets(s, sizeof(s), stdin) != NULL) 
				break;
		}
		printf("Aleksandrov(31) OK! \n");
		kill(getppid(), SIGKILL);//to parent
	}
	return(0);
}
