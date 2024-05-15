#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#define IO_TIME 30

typedef struct job {
int id;
int arrival;
int unblock;
int exectime;
float ioratio;
struct job *next;
int turnaround;
int respons;
} job;

typedef struct spec{
int arrival;
int exectime;
float ioratio;
} spec;

spec specs [ ] = {
{ 0, 10, 0.0 },
{ 0, 30, 0.7 },
{ 0, 20, 0.0 },
{ 40, 80, 0.4 },
{ 60, 30, 0.3 },
{120, 90, 0.3 },
{120, 40, 0.5 },
{140, 20, 0.2 },
{160, 10, 0.3 },
{180, 20, 0.3 },
{0 , 0 , 0} // dummy job
};

/*spec specs [ ] = {
{0, 5, 0.0},
{0, 3, 0.0},
{0, 7, 0.0},
{0, 1, 0.0},
{0, 0, 0}
};*/

job * readyq = NULL;
job * blockedq = NULL;
job *doneq = NULL;

int ext = 0;
int tot = 0;
int cnt = 0;

int io_op (float ratio, int exect) {
	int io = ((float) rand ( )) / RAND_MAX < ratio;
	if (io)
		io = (int) trunc( ((float) rand()) / RAND_MAX * (exect - 1)) + 1;
	return io;
}

void block(job *this){
	job *nxt = blockedq;
	job *prev = NULL;
	while (nxt != NULL){
		if (this->unblock < nxt->unblock)
			break;
		else{
			prev = nxt;
			nxt = nxt->next;
		}
	}
	this->next = nxt;
	if (prev != NULL)
		prev->next = this;
	else{
		blockedq = this;
	}
	return;
}

void init( ){
	int i = 0 ;
	while (specs[ i ].exectime != 0 ) {
		job *new = (job*) malloc(sizeof (job));
		new->id = i+1;
		new->arrival = specs[i].arrival;
		new->unblock = specs[i].arrival;
		new->exectime = specs[i].exectime ;
		new->ioratio = specs[i].ioratio;
		new->turnaround = 0;
		new->respons = -1;
		block(new );
		i++;
		ext = ext + new->exectime;
	}
	cnt = i;
}

void ready (job *this){
	job *nxt = readyq;
	job *prev = NULL;
	while (nxt != NULL){
		//if (this->exectime < nxt->exectime)
		//	break;
		prev = nxt;
		nxt = nxt->next;
	}
	this->next = nxt;
	if (prev == NULL)
		readyq = this;
	else
		prev->next = this;
	return;
}

void unblock (int time){
	while (blockedq != NULL && blockedq->unblock<=time){
		job *nxt = blockedq;
		blockedq = nxt->next;
		printf("(%4d) unblock job %2d\n", time, nxt->id);
		ready(nxt);
	}
}

void done (job *this){
	this->next = doneq;
	doneq = this;
	return;
}

int schedule (int time, int slot){
	if (readyq != NULL){
		job *nxt = readyq;
		readyq = readyq->next;
		if (nxt->respons == -1)
			nxt->respons = time - nxt->arrival;
		int left = nxt->exectime;
		int exect = (left < slot) ? left : slot;
		//tt = tt + time - nxt->unblock + exect;
		//wt = wt + time - nxt->unblock;
		int io = 0;
		if (exect > 1){
			io = io_op(nxt->ioratio, exect);
			if (io)
				exect = io;
		}
		nxt->exectime -= exect;
		ext = ext + exect;
		printf("(%4d) run job %2d for %3d ms", time, nxt->id, exect);
		if (nxt->exectime == 0){
			nxt->turnaround = time + exect - nxt->arrival;
			tot = tot + nxt->turnaround;
			printf(" - done\n");
			done(nxt);
		}else{
			if (io){
				nxt->unblock = time + exect + IO_TIME;
				block(nxt);
				printf(" - %3d left-blocked \n", nxt->exectime);
			} else{
				ready(nxt);
				printf(" - %3d left\n", nxt->exectime);
			}
		}
		return exect;
	}
	else{
		return 1;
	}
}

int main(int argc, char *argv []){
	int slot = 5;
	if (argc == 2){
		slot = atoi(argv[1]);
	}
	init();
	int time = 0;
	while (blockedq != NULL || readyq != NULL){
		unblock(time);
		int tick = schedule(time, slot);
		time += tick;
	}
	printf("\n total execution time is %d \n", time);
	printf("tt is %.2f \n", 1.0*tot/cnt);
	printf("wt is %.2f \n", 1.0*(tot-ext)/cnt);
	return 0;
}
