#include <phase1.h>
#include <usloss.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
    -----------------------------
    |     STATUSES              |
    -----------------------------
*/
#define READY 1
#define RUNNING 2
#define BLOCKED 10

unsigned int PSR;
/* 
    -----------------------------
    |     Procces   Type         |
    -----------------------------
*/ 
typedef void (*Process)();

typedef struct PCBEntry {
    int pid;
    int priority;
    int status; 
    int isZapped;
    // Keep track of when the shit started 
    int timeSliceStart;
    // Keep track of how long it ran for
    int timeRanFor; 
    // Keep track of what zapped this process
    struct PCBEntry* zapList;
    // For proc table
    struct PCBEntry* parent;
    struct PCBEntry* firstChild;
    struct PCBEntry* nextChild;
    // For pq structure
    struct PCBEntry* nextPQ;

    char name[MAXNAME];
    USLOSS_Context context;
    Process func;
    // Args 
    char* args;

} PCBEntry;

// Current process running
typedef struct  CurrentProcess {
    PCBEntry* proccess;
} CurrentProcess;



CurrentProcess* currentProcess;

void proc_init(){
    currentProcess = malloc(sizeof(CurrentProcess));
}

/* 
    Add the child to the parent
*/
void proc_add(PCBEntry* parent,PCBEntry* child){
    if (parent->firstChild==NULL){
        parent->firstChild = child;
        child->parent = parent;
    } else {
        PCBEntry* curr = parent->firstChild;
        while (curr->nextChild!=NULL){
            curr = curr->nextChild;
        }
        curr->nextChild = child;
        child->parent = parent;
    }
}

/*  
    find lowest priority child
*/
int proc_find(PCBEntry* parent){
    PCBEntry* firstChild = parent->firstChild;
    PCBEntry* lowestChild = firstChild;

    while (firstChild!=NULL){
        if (firstChild->status == READY){
            if (firstChild->priority < lowestChild->priority){
                lowestChild = firstChild;
            }
            firstChild = firstChild->nextChild;
        }
    }

    if (lowestChild==NULL){
        return -1;
    }
    return lowestChild->pid;
}

/* 
    Print out parent and all it's children
*/
void proc_dump(PCBEntry* parent){
    printf("----- PROCESSS %s --------\n",parent->name);
    PCBEntry* child = parent->firstChild;
    while (child!=NULL){
        printf("%s\n",child->name);
        child = child->nextChild;
    }


}



/* 
    -----------------------------
    |    Proccess Table          |
    -----------------------------
*/  

// Proccess Table
PCBEntry* procTable[MAXPROC];

// Keeps track of pid to assign next
int curPID = 4;




/* 
    Finds a new pid number that is aviable due to the fact that the slot
    is open in the proc table
*/
int getPID(){
    int slot = curPID % MAXPROC;
    while (procTable[slot]!=NULL){
        slot = curPID % MAXPROC;
        curPID++;
    }
    

    return curPID;
}




/* 
    -----------------------------
    |     Priority Queue         |
    -----------------------------
*/  
int PQ_SIZE = 7;
PCBEntry*  priorityQueue[7];




/* 
    - first add the process procTable

    Adds to the priority queue
*/
void pq_add(int pid){
   
    //  Get process 
    int slot = pid % MAXPROC;
    PCBEntry* process = procTable[slot];
     
    // Get priority
    int priority = process->priority;
    int index = priority -1;

    if (priorityQueue[index]==NULL){
        priorityQueue[index] = process;
    } else {
        PCBEntry* head = priorityQueue[index];
        while (head->nextPQ!=NULL){
            head = head->nextPQ;
        }
        head->nextPQ = process;
    }
 
}

/* 
    Removes element from the priority queue
*/
void pq_remove(int pid){
    // Get the process & priority
    int slot = pid % MAXPROC;
    if (procTable[slot]==NULL){
        return;
    }
    PCBEntry* process = procTable[slot];
    int priority = process->priority;
     int index = priority -1;
    // Get the head of the pq 
    PCBEntry* head = priorityQueue[index];
    if (head->pid==pid){ 
        priorityQueue[index] = head->nextPQ;
        head->nextPQ=NULL;
    } else {
        PCBEntry* prev = head;
        while (head!=NULL){
            
            if (head->pid ==pid){
                prev->nextPQ = head->nextPQ;
                head->nextPQ=NULL;
            }
            prev = head;
            head = head->nextPQ;
        }
    }
}

/* 
    Pushs an element in the pq to end of 
    the linked list 
*/
void pq_pushToEnd(int pid){
    pq_remove(pid);
    pq_add(pid);
}

/* 
    Get the highest priority element in the queue
*/
int pq_get(){
    
    for (int i=0; PQ_SIZE>i;i++){
        if (priorityQueue[i]!=NULL){
                PCBEntry* head = priorityQueue[i];
                while (head!=NULL){
                    if (head->status == READY){
                        return head->pid;
                    }
                    head = head->nextPQ;
                }
        }
    }


    return -1;
}


/*
    Prints out the priority queue
*/
void pq_dump(){
    printf("\n\n------------- PQ -------------------\n\n");
    for (int i=0; PQ_SIZE>i;i++){
        PCBEntry* process = priorityQueue[i];
        printf("------------ %d ------------\n",i+1);
        if (process==NULL){
            printf("null\n");
        } else {
            while (process!=NULL){
                printf("name:%s\n",process->name);
                process = process->nextPQ;
            }
        }
    }
    printf("\n\n------------- PQ -------------------\n\n");
}



/* 
    -----------------------------
    |      DISPATCHER            |
    -----------------------------
*/  
void dispatcher(){
    /* 
        Get highest priority pq
    */
    int pid = pq_get();
    
    /*  
        Call the function
    */
    // procTable[pid]->func(procTable[pid]->args);
}


/* 
    -----------------------------
    |     CORE FUNCTIONS        |
    -----------------------------
*/  

void sentinel_init_func(){
     while (1) {
        if (phase2_check_io() == 0){
            // report deadlock and terminate simulation
        }
        USLOSS_WaitInt();
     }

}

int checkMode(){
    
}

void process_init_func(){
    // Add to pq
    pq_add(currentProcess->proccess->pid);
    

    // Create sentinel process
    PCBEntry* sentinel = malloc(sizeof(PCBEntry));
    sentinel->pid = 2;
    sentinel->priority = 7;
    sentinel->status = READY;
    sentinel->parent = NULL;
    sentinel->firstChild = NULL;
    sentinel->nextChild = NULL;
    sentinel->nextPQ=NULL;
    strcpy(sentinel->name,"sentinel");
    sentinel->func = sentinel_init_func;
    procTable[2 % MAXPROC] = sentinel;  
    // Add to pq
    pq_add(sentinel->pid);
    // Add as child
    proc_add(currentProcess->proccess,sentinel);

    

    // Create testcase main process
    PCBEntry* main = malloc(sizeof(PCBEntry));
    main->pid = 3;
    main->priority = 5;
    main->status = READY;
    main->parent = NULL;
    main->firstChild = NULL;
    main->nextChild = NULL;
    main->nextPQ = NULL;
    strcpy(main->name,"main");
    main->func = testcase_main;
    procTable[3 % MAXPROC] = main;   
    // Add to pq
    pq_add(main->pid);
    // Add as child 
    proc_add(currentProcess->proccess,main);
   

    
    // Call functions
    phase2_start_service_processes();
	phase3_start_service_processes();
	phase4_start_service_processes();
	phase5_start_service_processes();
	testcase_main();
    // 
    while (1){
        join(0);
    }
}
     
    
    

    


// 
void  phase1_init(void){
    
    // Make init process
    PCBEntry* init = malloc(sizeof(PCBEntry));
    init->pid = 1;
    init->priority = 1;
    init->status = READY;
    init->parent = NULL;
    init->firstChild = NULL;
    init->nextChild = NULL;
    init->nextPQ = NULL;
    strcpy(init->name,"init");
    init->func = process_init_func;
    procTable[1 % MAXPROC] = init;   

    // Intilaze current process 
    proc_init();
    currentProcess->proccess = init;

}

int  fork1(char *name, int(*func)(char *), char *arg, int stacksize, int priority){
    // Create new process
    int pid = getPID();
    PCBEntry* newProcess = malloc(sizeof(PCBEntry));
    newProcess->pid = pid;
    newProcess->priority = priority;
    newProcess->status = READY;
    newProcess->parent = NULL;
    newProcess->firstChild = NULL;
    newProcess->nextChild = NULL;
    newProcess->nextPQ = NULL;
    char text[MAXNAME];
    sprintf(text, "proc - %d", pid);
    strcpy(newProcess->name,text);
    newProcess->func = func;
    procTable[pid % MAXPROC] = newProcess;   
    // Add to pq
    pq_add(newProcess->pid);
    // Add as child
    proc_add(currentProcess->proccess,newProcess);

    // Call dispatcher
    dispatcher();
    return 0;
}


int   join(int *status){
    return 0;
}

void  quit(int status){
    return ;
}

int  zap(int pid){
    return 0;
}

/* 
    Tells wether it is zapped or not,
    1 - it is
    0 - it is not
*/
int   isZapped(void){
    return currentProcess->proccess->isZapped;
}

/* 
    Gets pid of current running process
*/
int   getpid(void){
    return currentProcess->proccess->pid;
}

 
/* 
    Prints out the entire proc table
*/  
void printProcess(PCBEntry* process){
    if (process == NULL){
            printf("NULL");
        } else {
            printf("Name:          |%s\n",process->name);
            printf("PID:           |%d\n",process->pid);
            // Parent pid
            int parentPid = -1;
            if (process->parent != NULL){
                parentPid = process->parent->pid;
            }
            printf("Parent PID:    |%d\n",parentPid);
            // Priority
            printf("Priority:      |%d\n",process->priority);
            printf("status:        |%d\n",process->status);
            // # of children
            int childrenNum = 0;
            PCBEntry* curr = process->firstChild;
            while (curr!=NULL){
                curr = curr->nextChild;
                childrenNum++;
            }
            printf("# of children: |%d\n",childrenNum);
            // Time consumed
            printf("Time consumed: |%d\n",process->timeRanFor);
        }
}

void  dumpProcesses(void){
    printf("---------------------------\n");
    for (int i=0;MAXPROC>i;i++){
        printf("---------------------------\n");
        printProcess(procTable[i]);
        printf("\n---------------------------");
        
    }
    printf("\n");
}

/* 
    Block the current process
*/
int   blockMe(int block_status){
    if (block_status < 10){
        printf("Block status must be above yes is %d\n",block_status);
        USLOSS_Halt(1);
    }
    // Set to block
    currentProcess->proccess->status = block_status;
    // Call dispacther
    dispatcher();
    return 0;
}

/* 
    UnBlocks a process 
*/
int   unblockProc(int pid){
    int slot = pid % MAXPROC;
    // Cant un block null
    if (procTable[slot]==NULL){
        return -2;
    }
    PCBEntry* proccess = procTable[slot];
    // Cant un block youself
    if (proccess->pid==pid){
        return -2;
    }
    int status = proccess->status;
    // Can't un block an unblocked process
    if (status<BLOCKED){
        return -2;
    }

    // Change status to ready
    proccess->status = READY;
    // Push to the end of the pq
    pq_pushToEnd(proccess->pid);

    // Call dispacther
    dispatcher();
    return 0;
}

int   readCurStartTime(void){
    return currentProcess->proccess->timeSliceStart;
}

void  timeSlice(void){
    return ;
}

int   readtime(void){
    return 0;
}

int   currentTime(void){
    return 0;
}

void  startProcesses(void){
    /* 
        Intialze init process and its children
    */
    PSR = USLOSS_PsrGet();
    phase1_init();
   
   
    /* 
        Call the init process
    */
    procTable[1]->func();
    
    
}



