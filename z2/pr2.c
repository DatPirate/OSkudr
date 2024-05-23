#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
int count = 0;
void SigHndlr (int s) {
	printf("\nAleksandrov(31) I got SIGINT %d time(s) \n", ++ count);
	if (count == 5) signal (SIGINT, SIG_DFL);
	else signal (SIGINT, SigHndlr);
}
int main (int argc, char **argv) {
	signal (SIGINT, SigHndlr);
	while (1);
	return(0);
}
