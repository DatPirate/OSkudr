#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct job {
int id;
int arrival;
int unblock;
int exectime;
float ioratio;
struct job *next;
int respons;
int prev;
} job;

typedef struct spec{
int arrival;
int exectime;
float ioratio;
} spec;

/*spec specs [ ] = {
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
};*/

spec specs [ ] = {
{0, 13, 0.0},
{0, 4, 0.0},
{0, 1, 0.0},
{0, 0, 0}
};

job * readyq = NULL;
job * blockedq = NULL;
job *doneq = NULL;

int tt = 0;
int wt = 0;
int cnt = 0;



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
		new->respons = -1;
		new->prev = 0;
		block(new );
		i++;
	}
	cnt = i;
}

void ready (job *this){
	job *nxt = readyq;
	job *prev = NULL;
	while (nxt != NULL){
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
		if (nxt->respons == -1){
			nxt->respons = time - nxt->arrival;
			wt = wt + nxt->respons;
		}else wt = wt + time - nxt->prev;
		int left = nxt->exectime;
		int exect = (left < slot) ? left : slot;
		tt = tt + exect;
		nxt->exectime -= exect;
		printf("(%4d) run job %2d for %3d ms", time, nxt->id , exect);
		if (nxt->exectime == 0){
			//nxt->turnaround = time + exect - nxt->arrival;
			printf(" = done\n");
			done(nxt) ;
		} else{
			nxt->prev = time + exect;
			ready (nxt);
			printf( "=%3d left \n", nxt->exectime);
		}
		return exect;
	}
	else{
		return 1;
	}
}

int main(int argc, char *argv []){
	int slot = 1;
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
	printf("tt is %.2f \n", 1.0*(tt+wt)/cnt);
	printf("wt is %.2f \n", 1.0*wt/cnt);
	return 0;
}
