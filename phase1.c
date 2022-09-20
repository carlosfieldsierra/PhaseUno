#include <phase1.h>
#include <usloss.h>
#include <stdio.h>




typedef void (*Process)();

typedef struct PCBEntry {
    int pid;
    int priority;
    struct PCBEntry* parent;
    struct PCBEntry* firstChild;
    struct PCBEntry* nextChild;
    char procName[MAXNAME];
    USLOSS_Context context;
    Process func;

} PCBEntry;

struct PCBEntry procTable[MAXPROC];

void initProc(){
    //init process
    //TODO: create sentinel proc
    //TODO: create testcase_main proc
	phase2_start_service_processes();
	phase3_start_service_processes();
	phase4_start_service_processes();
	phase5_start_service_processes();
	testcase_main();
        while (1){
                join(0);
        }
}


/* 

*/
void  phase1_init(void){
    // Create first process
    struct PCBEntry init;
    init.pid = 1;
	init.priority = 6;
	init.parent = NULL;
	init.firstChild = NULL;
	init.nextChild = NULL;
	strcpy( init.procName, "init");
	init.func = initProc;
	int slot = 1 % MAXPROC;
	procTable[slot] = init;	
    dispatcher();

};

void dispatcher(){
    
}

int getSize(char *a){
   return sizeof(a)/sizeof(a[0]);
}
int  fork1(char *name, int(*func)(char *), char *arg, int stacksize, int priority){
    // Error check
    if (stacksize < USLOSS_MIN_STACK) return -2;
    if (arg==NULL || getSize(arg) >MAXNAME) {
        return -1;
    }
    printf("dad\n");

    int pid = 4;
    int slot = pid % MAXPROC;
    struct PCBEntry newEntry;
	procTable[slot] = newEntry;
	newEntry.pid = pid;
	newEntry.priority = priority;	

    func(arg);
    mmu_init_proc(pid);
	dispatcher(); 
	return pid;
};

int   join(int *status){
    return 0;
};

void quit(int status){
    return;
};

int   zap(int pid){
    return 0;
};

int   isZapped(void){
    return 0;
};

int   getpid(void){
    return 0;
};

void  dumpProcesses(void){
    return;
};

int   blockMe(int block_status){
    return 0;
};

int   unblockProc(int pid){
    return 0;
};

int   readCurStartTime(void){
    return 0;
};

void  timeSlice(void){
    return;
};

int   readtime(void){
    return 0;
};

int   currentTime(void){
    return 0;
};

void  startProcesses(void){

    phase1_init();

	procTable[1].func();	
};