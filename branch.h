#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define null NULL

#define max_number_nodes 1500000000

int x[200];	//hardcoded limit!
int tipper;
int tipper_stack[100];
int supress=-1;
int node_count=0;
int node_local[100];
int state_count=0;
int state_local[100];
int loop_num;

class node
{
public:
	char x;
	char n;	
	node* above;
/*	
	node() {
		x = 0;
		n = 0;
		above = null;
	}
*/	
	node(int tx, int tn, node* ta){
		x = tx;
		n = tn;
		above = ta;
		if(++node_count>max_number_nodes) {
			printf("out of ram!\n");
			exit(0);
		}
		++node_local[loop_num];
	}
	
	~node(){
		--node_count;
		--node_local[loop_num];
	}
	
	void remove(){
		if(above != null) {
			above->n--;
			if(above->n <= 0) above->remove();
		}
		delete this;
	}
	
	
};


class state
{
public:
	node* cur;
	state* next;
	
	state(){
		cur = null;
		next = null;
		++state_count;
//		printf("%5d, %3d,  ",loop_num,state_local[loop_num]);
		++state_local[loop_num];
//		printf("%7d,",state_count);
	}
	
	~state(){
		--state_count;
		--state_local[loop_num];
	}
};


state* list;		//current solution list
node* base;			//the base node of the tree
int xer;
state* back[100];
node* up; 
node* mid;
state* down;
state* temp_list;
state* here[100]; //stack for loop
state* down_back;
int prev_ct;
node* scaner;

//you get 2721600 nodes for 100 megs ram...with an int x or a char x.

int start_time, cur_time, prev_time;

void init();
void init()
{
	if(node_count >1) printf( "MEMORY LEAK of %d nodes\n", node_count);
	if(state_count >1) printf( "MEMORY LEAK of %d states\n", state_count);
	loop_num=0;
	node_count = 0;
	state_count = 0;
	node_local[0] = 0;
	state_local[0] = 0;
	base = new node(0,1,null);
	list = new state(); 
	(*list).cur=base;
	(*list).next=null;
	for(int i=0; i<200; ++i) x[i]=-i;//WARNING!  MAY BREAK OTHER PROGRAMS!
	start_time=clock();
	tipper=0;
	prev_ct=1;
}

void branch(int, int);
void branch(int min, int max)
{
	if(state_count==0) {init(); printf("boom\n");}
	if(node_count*(max-min+1) > max_number_nodes ){
		printf("\nout of ram!\n");
		exit(1);
	}
	prev_time=clock();
	++tipper;
	down_back = new state();		//previous post-branch location
	temp_list = down_back;		//store start of list till branch finishes
	for(here[loop_num] = list; here[loop_num]!=null; here[loop_num]=(*here[loop_num]).next){
		for(int i=min; i<=max; ++i)
		{
			down = new state();
			(*down).cur= new node(i,0,here[loop_num]->cur);
			++(*(*here[loop_num]).cur).n;
			(*down_back).next=down;
			down_back=down;
		}
	}
	(*down).next=null;
	while(list!=null)
	{
		back[loop_num]=list;
		list=(*list).next;
		delete back[loop_num];
	}	
	list = (*temp_list).next;
	cur_time=clock();
	printf("branch%3d from%3d to%3d,%8d/%8d s and%9d/%9d n,%6d ms of%7d ms, bf = %8f\n",
		   tipper-1, min, max,state_local[loop_num],state_count,node_local[loop_num],node_count,((cur_time-prev_time)*1000)/CLOCKS_PER_SEC,((cur_time-start_time)*1000)/CLOCKS_PER_SEC,double(state_count)/double(prev_ct));
}

#define prune prev_time=clock(); rune

#define rune \
	back[loop_num] = new state(); \
	(*back[loop_num]).next=list; \
	list=back[loop_num]; \
	for(here[loop_num] = (*list).next; here[loop_num]!=null; back[loop_num]=here[loop_num], here[loop_num]=(*here[loop_num]).next) { \
		xer=1; \
		for(scaner = (*here[loop_num]).cur; (*scaner).above!=null; scaner=(*scaner).above) \
		{ \
			x[tipper-xer++]=(*scaner).x; \
		}
			//above line causes x to be 0 indexed, the number for each branch is the number of previous branches
		//CONDITIONAL GOES HERE
#define ill \
		{ \
			here[loop_num]->cur->remove(); \
			back[loop_num]->next = here[loop_num] -> next; \
			delete here[loop_num]; \
			here[loop_num] = back[loop_num]; \
		} \
	} \
	back[loop_num] = list; \
	list=(*list).next; \
	delete back[loop_num];


#define kill ill cur_time=clock(); \
	printf("pruned                 ,%8d/%8d s and%9d/%9d n,%6d ms of%7d ms, bf = %8f\n",state_local[loop_num],state_count,node_local[loop_num],node_count,((cur_time-prev_time)*1000)/CLOCKS_PER_SEC,((cur_time-start_time)*1000)/CLOCKS_PER_SEC,double(state_local[loop_num])/double(prev_ct)); \
	prev_ct = state_local[loop_num];


#define sprint \
rune \
	for(int foox =0; foox<5; ++foox){ \
	for(int ix=0; ix<=5; ++ix){ \
		printf("%c ",x[ix*5+foox]+'`'); \
	} \
	printf("\n"); \
	} \
	printf("\n"); \
if(0) ill

//file dependent
#define print \
rune \
	for(int ix=0; ix<=80; ++ix){ \
		fprintf(fp,"%d",x[hash[ix]]); \
	} \
	fprintf(fp,"\n"); \
if(0) ill \
fflush(fp);


int max, min;
int iocount;

#define inline_branch min = 
#define to ; max =
#define inline_prune ; \
	if(state_local[loop_num]==0) {init(); printf("boom\n");} \
	if(node_count > max_number_nodes ) \
	{ \
		printf("\nout of ram!\n"); \
		exit(1); \
	} \
	iocount = 0; \
	prev_time=clock(); \
	++tipper; \
	down_back = new state(); \
	temp_list = down_back; \
	back[loop_num] = new state(); \
	(*back[loop_num]).next = list; \
	list = back[loop_num]; \
	for(here[loop_num] = list->next; here[loop_num]!=null; here[loop_num]=(*here[loop_num]).next) \
	{ \
		xer=2; \
		for(scaner = (*here[loop_num]).cur; (*scaner).above!=null; scaner=(*scaner).above) \
		x[tipper-xer++]=(*scaner).x; \
		if(++iocount%1000000==0){printf("."); fflush(stdout);} \
		if(iocount%100000000==0){printf("\n"); fflush(stdout);} \
		for(int ii = min; ii <= max; ++ii) \
		{ \
			x[tipper-1] = ii;
		//CONDITIONAL goes here
#define nokill {\
				down = new state(); \
				(*down).cur= new node(ii,0,(here[loop_num]->cur)); \
				(*down_back).next=down; \
				down_back=down; \
				++(*(*here[loop_num]).cur).n; \
			} \
		} \
		up=(*(*here[loop_num]).cur).above; \
		mid=(*here[loop_num]).cur; \
		if((*mid).n==0) \
		{ \
			back[loop_num]->next = here[loop_num]->next; \
			delete here[loop_num]; \
			here[loop_num] = back[loop_num]; \
		} \
		while((*mid).n==0) \
		{ \
			delete mid; \
			--(*up).n; \
			mid=up; \
			up=(*mid).above; \
		} \
		back[loop_num] = here[loop_num]; \
	} \
	(*down).next=null; \
	while(list!=null) \
	{ \
		back[loop_num]=list; \
		list=(*list).next; \
		delete back[loop_num]; \
	} \
	list = (*temp_list).next; \
	delete temp_list; \
	cur_time=clock(); \
	printf("branch%3d from%3d to%3d,%8d/%8d s and%9d/%9d n,%6d ms of%7d ms, bf = %8f\n",tipper-1, min, max,state_local[loop_num],state_count,node_local[loop_num],node_count,((cur_time-prev_time)*1000)/CLOCKS_PER_SEC,((cur_time-start_time)*1000)/CLOCKS_PER_SEC,double(state_local[loop_num])/double(prev_ct)); \
	fflush(NULL); \
	prev_ct = state_local[loop_num];


#define loop \
	tipper_stack[loop_num] = tipper; \
	rune \
		for(int i=tipper; i<100; ++i) x[i]=-i; \
		++loop_num; \
		prev_ct = 1; \
		node_local[loop_num] = 0; \
		state_local[loop_num] = 0; \
		base = new node(0,1,null); \
		list = new state(); \
		(*list).cur=base; \
		(*list).next=null; \
		printf("\n  LOOP%3d on %8d s,%8d/%8d s and%9d/%9d n,%6d ms of%7d ms, bf = %8f\n",tipper-1, state_local[loop_num-1],state_local[loop_num],state_count,node_local[loop_num],node_count,((cur_time-prev_time)*1000)/CLOCKS_PER_SEC,((cur_time-start_time)*1000)/CLOCKS_PER_SEC,double(state_local[loop_num])/double(prev_ct));

//do loop stuff in here
#define endloop \
if(state_local[loop_num] >0) {rune if(1) ill} \
		if(node_local[loop_num] > 1) printf( "MEMORY LEAK of %d nodes\n", node_local[loop_num]); \
		if(state_local[loop_num] !=0) printf( "MEMORY LEAK of %d states\n", state_local[loop_num]); \
		--loop_num; \
 		tipper = tipper_stack[loop_num]; \
	if(1) ill
