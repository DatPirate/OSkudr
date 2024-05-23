#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
const char *tempfile = "abc1";
void sighandler(int signum) {
	printf("Aleksandrov(31) Caught signal %d, coming out...\n", signum);
	unlink(tempfile);
	exit(0);
}
int main () {
	signal(SIGINT, sighandler);
	creat(tempfile, 0666);
	sleep(8);
	unlink(tempfile);
	return(0);
}
