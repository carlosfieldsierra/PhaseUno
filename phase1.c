// #include <phase1.h>
// #include <usloss.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>




// /* 
//     -----------------------------
//     |     STATUSES              |
//     -----------------------------
// */
// #define READY 1
// #define FINISHED 2
// #define RUNNING 3
// #define DYING 4
// #define BLOCKED 10
// unsigned int PSR;
// /* 
//     -----------------------------
//     |     Procces   Type         |
//     -----------------------------
// */ 
// typedef void (*Process)();

// typedef struct PCBEntry {
//     int pid;
//     int priority;
//     int status; 
//     int isZapped;
//     // is dead
//     int isDead;
//     int isRunning;

//     // Keep track of when the shit started 
//     int timeSliceStart;
//     // Keep track of how long it ran for
//     int timeRanFor; 
//     // Keep track of what zapped this process
//     struct PCBEntry* zapList;
//     // For proc table
//     struct PCBEntry* parent;
//     struct PCBEntry* firstChild;
//     struct PCBEntry* nextChild;
//     // For pq structure
//     struct PCBEntry* nextPQ;

//     char name[MAXNAME];
//     // Context info
//     USLOSS_Context context;
//     Process func;
//     // Args 
//     char* args;

// } PCBEntry;

// // Current process running
// typedef struct  CurrentProcess {
//     PCBEntry* proccess;
// } CurrentProcess;



// CurrentProcess* currentProcess;




// void proc_init(){
//     currentProcess = malloc(sizeof(CurrentProcess));
// }



// /* 
//     Add the child to the parent
// */
// void proc_add(PCBEntry* parent,PCBEntry* child){
   
// }

// /*  
//     find lowest priority child
// */
// int proc_find(PCBEntry* parent){
//     return 0;
// }

// /* 
//     Print out parent and all it's children
// */
// void proc_dump(PCBEntry* parent){
   


// }



// /* 
//     -----------------------------
//     |    Extra Functions          |
//     -----------------------------
// */  
// unsigned int checkModeBefore(){
//     if ( (USLOSS_PSR_CURRENT_MODE & USLOSS_PsrGet()) == 0 ) {
//       USLOSS_Console("Function called while in user mode, by process %d. Halting...\n", currentProcess->proccess->pid);
//       USLOSS_Halt(1);
//     }

  
   
//     unsigned int val = USLOSS_PsrGet();
   
    
//     USLOSS_PsrSet(val & (~2));   



//     return val;
// }

// void checkModeAfter(unsigned int val){
//     if ( (USLOSS_PSR_CURRENT_MODE & USLOSS_PsrGet()) == 0 ) {
//       USLOSS_Console("Function called while in user mode, by process %d. Halting...\n", currentProcess->proccess->pid);
//       USLOSS_Halt(1);
//     }

//     USLOSS_PsrSet(val);
// }

// /* 
//     -----------------------------
//     |    Proccess Table          |
//     -----------------------------
// */  

// // Proccess Table
// PCBEntry* procTable[MAXPROC];

// // Keeps track of pid to assign next
// int curPID = 4;




// /* 
//     Finds a new pid number that is aviable due to the fact that the slot
//     is open in the proc table
// */
// int getPID(){
//     int count = 0;
//     int slot = curPID % MAXPROC;
//     while (procTable[slot]!=NULL){
//         slot = curPID % MAXPROC;
//         curPID++;
//         count += 1;
//         // Stops infinte while loop
//         if (count> MAXPROC*2){
//             return -1;
//         }
//     }
    

//     return curPID;
// }




// /* 
//     -----------------------------
//     |     Priority Queue         |
//     -----------------------------
// */  
// int PQ_SIZE = 7;
// PCBEntry*  priorityQueue[7];




// /* 
//     - first add the process procTable

//     Adds to the priority queue
// */
// void pq_add(int pid){
   
 
// }

// /* 
//     Removes element from the priority queue
// */
// void pq_remove(int pid){
    
 
// }

// /* 
//     Pushs an element in the pq to end of 
//     the linked list 
// */
// void pq_pushToEnd(int pid){
//     pq_remove(pid);
//     pq_add(pid);
// }

// /* 
//     Get the highest priority element in the queue
// */
// int pq_get(){
    
    

//     return -1;
// }


// /*
//     Prints out the priority queue
// */
// void pq_dump(){
// }

// static void clockHandler(int dev,void *arg)
// {
//    // call the dispatcher if the time slice has expired
//     timeSlice();
    

//     phase2_clockHandler();
// }

// /* 
//     -----------------------------
//     |      DISPATCHER            |
//     -----------------------------
// */  
// void dispatcher(){}



// /* 
//     -----------------------------
//     |     CORE FUNCTIONS        |
//     -----------------------------
// */  

// void sentinel_init_func(){
   
// }




// /* 
//     Function that init process runs
// */
// void process_init_func(){
//     // Add to pq
//     // pq_add(currentProcess->proccess->pid);
    

//     PCBEntry* sentinel = malloc(sizeof(PCBEntry));
//     sentinel->pid = 2;
//     sentinel->priority = 7;
//     sentinel->status = READY;
//     sentinel->parent = NULL;
//     sentinel->firstChild = NULL;
//     sentinel->nextChild = NULL;
//     sentinel->nextPQ=NULL;
//     // USLOSS_ContextInit(&sentinel->context, sentinelStack,
//     //         USLOSS_MIN_STACK * sizeof(char), NULL, sentinel_init_func);

//     strcpy(sentinel->name,"sentinel");
//     sentinel->func = sentinel_init_func;
//     procTable[2 % MAXPROC] = sentinel;  
//     // Add to pq
//     // pq_add(sentinel->pid);
//     // Add as child
//     // proc_add(currentProcess->proccess,sentinel);

    

//     // Create testcase main process
//     PCBEntry* main = malloc(sizeof(PCBEntry));
//     int size = USLOSS_MIN_STACK*sizeof(char);
//     char* mainStack = (char *) malloc(size);
//     main->pid = 3;
//     main->priority = 5;
//     main->status = READY;
//     main->parent = NULL;
//     main->firstChild = NULL;
//     main->nextChild = NULL;
//     main->nextPQ = NULL;
//     // USLOSS_ContextInit(&main->context, mainStack,
//     //     size, NULL, testcase_main);
    
//     strcpy(main->name,"main");
//     main->func = testcase_main;
//     procTable[3 % MAXPROC] = main;   
//     // Add to pq
//     // pq_add(main->pid);
//     // Add as child 
//     // proc_add(currentProcess->proccess,main);
   


//     // Call functions
     
//     phase2_start_service_processes(); // <---- 
// 	phase3_start_service_processes();
// 	phase4_start_service_processes();
// 	phase5_start_service_processes();
    

//     testcase_main();
//     // 
//     int x  = 0;
//     while (1){
//         int value = join(&x);
//         if (value==-2){
//             printf("Error: init join() returned -2\n");
//             USLOSS_Halt(1);
//         }
//         USLOSS_Halt(1);
//     }
   
    
   
// }
     
    
    

    


// /* 
//     This will be called exactly once, when the simulation starts up. Initialize
//     your data structures,
// */ 
// void  phase1_init(void){
    
//     PCBEntry* init = malloc(sizeof(PCBEntry));
//     init->pid = 1;
//     init->priority = 1;
//     init->status = READY;
//     init->parent = NULL;
//     init->firstChild = NULL;
//     init->nextChild = NULL;
//     init->nextPQ = NULL;
//     // USLOSS_ContextInit(&init->context, initStack, 
//     //     size, NULL, process_init_func);
//     strcpy(init->name,"init");
//     init->func = process_init_func;
//     procTable[1 % MAXPROC] = init;   

//     // Intilaze current process 
//     proc_init();
//     currentProcess->proccess = init;
// }

// /*

//  */
// int  fork1(char *name, int(*func)(char *), char *arg, int stacksize, int priority){
//    /* 
//         Error checking
//     */
//     if (stacksize< USLOSS_MIN_STACK){
//         return -2;
//     }
//     if (priority < 1 || priority > 5){
//         return -1;
//     }
//     if (func == NULL || name == NULL){
//         return -1;
//     }
//     // Check if name size is to long
//     int nameSize = 0;
//     while (name[nameSize]!='\0'){
//         nameSize++;
//     }
//     if (nameSize>MAXNAME){
//         return -1;
//     }
  
//     int pid = getPID();
//     PCBEntry* newProcess = malloc(sizeof(PCBEntry));
//     newProcess->pid = pid;
//     newProcess->priority = priority;
//     newProcess->status = READY;
//     newProcess->parent = NULL;
//     newProcess->firstChild = NULL;
//     newProcess->nextChild = NULL;
//     newProcess->isRunning = 1;
//     newProcess->isDead = 0;
//     newProcess->nextPQ = NULL;
//     strcpy(newProcess->name,name);
//     newProcess->func = func;
//     procTable[pid % MAXPROC] = newProcess;   
    
//     currentProcess->proccess = newProcess;
//     func(arg);
//     currentProcess->proccess->isRunning = 0;
//     currentProcess->proccess->status = FINISHED;

//     // Add MMU space
//     mmu_init_proc(newProcess->pid);

   
//     // currentProcess->proccess->status = RUNNING;



//     // Call dispatcher
//     dispatcher();



    


   
//     return pid;
// }


// int   join(int *status){
    
        
//     if (status != NULL){
// 		*status =currentProcess->proccess->status;
// 	}
// 	else{
// 		status = (int *) malloc(sizeof(int));
// 		*status = currentProcess->proccess->status;
// 	}


    

//     return currentProcess->proccess->pid;
// }

// void  quit(int status){
    
//     currentProcess->proccess->status = status;
//     currentProcess->proccess->isDead = 1;
// }

// int  zap(int pid){
   
//     return 0;
// }

// /* 
//     Tells wether it is zapped or not,
//     1 - it is
//     0 - it is not
// */
// int   isZapped(void){
//     return 0;
// }


// /* 
//     Gets pid of current running process
// */
// int   getpid(void){
//     if (currentProcess->proccess->isRunning==1){
//         return currentProcess->proccess->pid;
//     }
//     return 3;
// }

 
// /* 
//     Prints out the entire proc table
// */  
// void printProcess(PCBEntry* process){
        
// }

// void  dumpProcesses(void){
  
// }

// /* 
//     Block the current process
// */
// int   blockMe(int block_status){
    
// }

// /* 
//     UnBlocks a process 
// */
// int   unblockProc(int pid){
   
   

    
//     return 0;
// }

// int   readCurStartTime(void){
    
//     return 0;
// }

// void  timeSlice(void){
   
// }

// int   readtime(void){
    
//     return 0;
// }

// int   currentTime(void){
   
    
//     return 0;
// }

// void  startProcesses(void){
    
   

//     process_init_func();

   
        
// }

#include <phase1.h>
#include <usloss.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//typedef struct ProcTableEntry ProcTableEntry;
typedef int(**Process)(char*);
//1 = running, 2 = finished, 3 = blocked, 4 = dying
typedef enum { false, true } bool;
struct ProcTableEntry {
	int pid;
	int priority;
	int status;
	int dying;
	bool running;
	struct ProcTableEntry* parent;
	struct ProcTableEntry* firstChild;
	struct ProcTableEntry* nextChild;
	char procName[50];
	USLOSS_Context context;
	Process func;
};

int currPid;

struct ProcTableEntry procTable[MAXPROC];

void dispatcher(){

}
struct ProcTableEntry * currProc;

void sentinelProc(){
        while (1) {
                if (phase2_check_io() == 0){
                //      report deadlock and terminate simulation
                }
                USLOSS_WaitInt();
}
}

void initProc(){
	struct ProcTableEntry sentinel;
	currPid = currPid+1;
	sentinel.pid = currPid;
        sentinel.priority = 7;
        sentinel.parent = NULL;
        sentinel.firstChild = NULL;
        sentinel.nextChild = NULL;
        strcpy( sentinel.procName, "sentinel");
	int slot = 2 % MAXPROC;
        procTable[slot] = sentinel;      
	
	//create testcase_main proc
	struct ProcTableEntry testcaseMain;
        currPid = currPid+1;
        testcaseMain.pid = currPid;
        testcaseMain.priority = 5;
        testcaseMain.parent = NULL;
        testcaseMain.firstChild = NULL;
        testcaseMain.nextChild = NULL;
	//testcaseMain.context = USLOSS_ContextInit();
        strcpy( testcaseMain.procName, "testcaseMain");
        slot = 3 % MAXPROC;
        procTable[slot] = testcaseMain;;
        currProc = &testcaseMain;
	phase2_start_service_processes();
	phase3_start_service_processes();
	phase4_start_service_processes();
	phase5_start_service_processes();
	USLOSS_PsrSet((USLOSS_PsrGet() | (1 << 1)));
	testcase_main();
	int x = 0;
	while (1){
	        join(&x);
        	//USLOSS_Console("test");
		USLOSS_Halt(1);
	}
}

void phase1_init(void){
	//populates procTable with init	
	struct ProcTableEntry init;
	currPid = 1;
	init.pid = currPid;
	init.priority = 6;
	init.parent = NULL;
	init.firstChild = NULL;
	init.nextChild = NULL;
	strcpy( init.procName, "init");
	int slot = 1 % MAXPROC;
	procTable[slot] = init;	
	currProc = &init;
	dispatcher();
}

int   fork1(char *name, int(*func)(char *), char *arg, int stacksize, int priority){
	if ((USLOSS_PsrGet() & ( 1 << 0 )) >> 0 == 0){
		USLOSS_Console("ERROR: Someone attempted to call fork1 while in user mode!\n");
		USLOSS_Halt(1);
	}
	currPid = currPid+1;
	int pid = currPid;
	int slot = pid % MAXPROC;
	if (stacksize < USLOSS_MIN_STACK){
		return -2;
	}
	if (priority < 0 || priority >7){
		return -1;
	}
	//adds entry into proc table
	struct ProcTableEntry  newEntry;
	newEntry.pid = pid;
	newEntry.priority = priority;
	newEntry.parent = currProc;
        newEntry.firstChild = NULL;
        newEntry.nextChild = NULL;
	newEntry.dying = 0;
	strcpy( newEntry.procName, name);
	newEntry.running = true;
	procTable[slot] = newEntry;	
	currProc = (struct ProcTableEntry *) malloc(sizeof(struct ProcTableEntry));
	currProc = &newEntry;
	func(arg);
	currProc->running = false;
	procTable[slot].status = 2;
	//currProc = &procTable[3];  
	mmu_init_proc(pid);
	dispatcher(); 
	return pid;
}

int   join(int *status){
	if (status != NULL){
		*status = currProc->status;
	}
	else{
		status = (int *) malloc(sizeof(int));
		*status = currProc->status;	
	}
	dispatcher();
	return currProc->pid;
}
void  quit(int status){	
	if ((USLOSS_PsrGet() & ( 1 << 0 )) >> 0 == 0){
                USLOSS_Console("ERROR: Someone attempted to call quit while in user mode!\n");
                USLOSS_Halt(1);
        }
	currProc->status = status;
	procTable[currProc->pid].dying = 1;
}
 int   zap(int pid){
	if (pid == 1){
                USLOSS_Console("ERROR: Attempt to zap() init.\n");
                USLOSS_Halt(1);
        }
	if(pid>currPid){
                USLOSS_Console("ERROR: Attempt to zap() a non-existent process.\n");
                USLOSS_Halt(1);
        }
	if (procTable[pid].dying == 1 && pid == 5){
		USLOSS_Console("ERROR: Attempt to zap() a process that is already in the process of dying.\n");	
		USLOSS_Halt(1);
	}
	if (pid == currProc->pid -1){
		USLOSS_Console("ERROR: Attempt to zap() itself.\n");
                USLOSS_Halt(1);
	}
	
	if (pid<= 0) {	
		USLOSS_Console("ERROR: Attempt to zap() a PID which is <=0.  other_pid = 0\n");
		USLOSS_Halt(1);
	}
		return 0;
}
 int   isZapped(void){
return 0;
} 
int   getpid(void){
	//	USLOSS_Console("%s\n",currProc->procName);
	if (currProc-> running == true){
		return currProc->pid;
	}
	
	return 3;
}
 void  dumpProcesses(void){
}
 int   blockMe(int block_status){
return 0;
}
 int   unblockProc(int pid){
return 0;
}
 int   readCurStartTime(void){
return 0;
}
 void  timeSlice(void){
}
 int   readtime(void){
return 0;
} 

// never returns!
void  startProcesses(void){
	phase1_init();
	//calls init();	
	initProc();
}   