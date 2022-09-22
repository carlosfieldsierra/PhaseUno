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
#define READY 1;
#define RUNNING 2;

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
PCBEntry* currentProccess;


void proc_init(){
    currentProccess = malloc(sizeof(currentProccess));
}

/* 
    Add the child to the parent
*/
void proc_add(PCBEntry* parent,PCBEntry child){
    
    if (parent->firstChild==NULL){
        parent->firstChild = malloc(sizeof(PCBEntry));
        parent->firstChild = &child;
        parent->firstChild->firstChild=NULL;
        parent->firstChild->nextChild=NULL;
        
    } else {
        
        while (parent->nextChild!=NULL){
            parent = parent->nextChild;
        }
        parent->nextChild = malloc(sizeof(PCBEntry));
        parent->nextChild = &child;
        parent->nextChild->firstChild=NULL;
        parent->nextChild->nextChild=NULL;
    }
}

/*  
    find lowest priority child
*/
void proc_find(PCBEntry parent){
    
}

/* 
    Print out parent and all it's children
*/
void proc_dump(PCBEntry* parent){
    printf("-------PARENT--------\n");
    // printProcess(*parent);
    printf("%s\n",parent->name);
    printf("-------CHILDREN--------\n");
    // PCBEntry* firstParent = parent;
    // while (parent!=NULL){

    //     printProcess(*parent);
    //     parent=parent->nextChild;
    // }
    // parent = firstParent;

}



/* 
    -----------------------------
    |    Proccess Table          |
    -----------------------------
*/  

// Proccess Table
PCBEntry procTable[MAXPROC];

// Keeps track of pid to assign next
int curPID = 4;



/* 
    Finds a new pid number that is aviable due to the fact that the slot
    is open in the proc table
*/
int getNewPID(){
    printf("here\n");
    // int slot = curPID % MAXPROC; 
    // int size = 0;
    // while (procTable[slot] == NULL){

    //     curPID++;
    //     slot = curPID % MAXPROC; 
    //     // Ensures that while loop exits if all pids 
    //     // in table are full
    //     size++;
    //     if (size > MAXPROC*2){
    //         printf("Error: PID are all full");
    //         exit(1);
    //     }
    // }

    return curPID;
}




/* 
    -----------------------------
    |     Priority Queue         |
    -----------------------------
*/  

PCBEntry  priorityQueue[6];
int PQ_SIZE = 7;


/* 
    Intilaize
*/
void pq_init(){
   for (int i=0; PQ_SIZE>i;i++){
        PCBEntry dummy;
        dummy.pid = -1;
        priorityQueue[i] = dummy ;
    }
}

/* 
    - first add the process procTable

    Adds to the priority queue
*/
void pq_add(int pid){
    //  Get process 
    int slot = pid % MAXPROC;
    PCBEntry process = procTable[slot];
    // Get priority
    int priority = process.priority;
    int index = priority -1;

    if (priorityQueue[index].pid==-1){
        priorityQueue[index] = process;
    } else {
        PCBEntry head = priorityQueue[index];
        while (head.nextPQ!=NULL){
            head = *head.nextPQ;
        }
        head.nextPQ = &process;
    }
 
}

void pq_remove(int pid){

}

void pq_pushToEnd(int pid){

}

int pq_get(){
    return 0;
}


/*
    Prints out the priority queue
*/


void pq_dump(){
    
    for (int i=0; PQ_SIZE>i;i++){
        PCBEntry process = priorityQueue[i];
        printf("------------ %d ------------\n",i+1);
        if (process.pid==-1){
            printf("null\n");
        } else {
            while (process.nextPQ != NULL){
                printf("name:%s\n",process.name);
                process = *process.nextPQ;
            }
            printf("name:%s\n",process.name);
        }
        printf("--------------------------\n",i);
    }
  
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
     if ( (USLOSS_PSR_CURRENT_MODE & USLOSS_PsrGet()) == 0 ) {
      USLOSS_Console("Function called while in user mode, by process %d. Halting...\n", currentProccess->pid);
      USLOSS_Halt(1);
    }
    return 1;
}

void process_init_func(){
    // Create sentinel process
    PCBEntry sentinel;
    sentinel.pid = 2;
    sentinel.priority = 7;
    
    sentinel.status = READY;
    sentinel.parent = NULL;
    sentinel.firstChild = NULL;
    sentinel.nextChild = NULL;
    sentinel.nextPQ=NULL;
    strcpy(sentinel.name,"sentinel");
    sentinel.func = sentinel_init_func;
    procTable[2 % MAXPROC] = sentinel;   
    pq_add(sentinel.pid);
    proc_add(currentProccess,sentinel);
   
    

   
    

     
    // Create testcase main process
   
    PCBEntry main;
    main.pid = 3;

    main.priority = 5;
    main.status = READY;
    main.parent = NULL;
    main.firstChild = NULL;
    main.nextChild = NULL;
    main.nextPQ = NULL;
    
    strcpy(main.name,"main");
    

    main.func = testcase_main;
    procTable[3 % MAXPROC] = main;  
    
    pq_add(main.pid);
    
    printf("IS NULL %d \n",currentProccess->firstChild==NULL);
    proc_add(currentProccess,main);
    
    proc_dump(currentProccess);
    

    

  
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


void  phase1_init(void){
    // Set everything in the proc table to NULL
    for (int i=0; MAXPROC>i;i++){
        PCBEntry dummy;
        dummy.pid = -1;
        procTable[i] =dummy ;
    }
    // Init the pq
    pq_init();
    // Init the current process 
    proc_init();
    

    struct PCBEntry init;

    init.pid =1;
    init.priority = 1;
    init.status = READY;
    init.parent = NULL;
    init.firstChild = NULL;
    init.nextChild = NULL;
    init.nextPQ = NULL;
    strcpy(init.name,"init");
    init.func = process_init_func;
    procTable[1 % MAXPROC] = init;   
    pq_add(init.pid);
    currentProccess = &init;
    



    

}

int   fork1(char *name, int(*func)(char *), char *arg, int stacksize, int priority){
        if (checkMode()){
            // Disable Interrupts
            USLOSS_PsrSet( USLOSS_PsrGet() & ~USLOSS_PSR_CURRENT_INT);
        }
        // Some code goes here
        
        if (checkMode()){
            // Restores Interrupts
            USLOSS_PsrSet(PSR);
        }
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

int   isZapped(void){
    return 0;
}

int   getpid(void){
    return 0;
}

/* 
    Prints out the entire proc table
*/  
void printProcess(PCBEntry process){
    if (process.pid == -1){
            printf("NULL");
        } else {
            printf("Name:          |%s\n",process.name);
            printf("PID:           |%d\n",process.pid);
            // Parent pid
            int parentPid = -1;
            if (process.parent != NULL){
                parentPid = process.parent->pid;
            }
            printf("Parent PID:    |%d\n",parentPid);
            // Priority
            printf("Priority:      |%d\n",process.priority);
            printf("status:        |%d\n",process.status);
            // # of children
            int childrenNum = 0;
            PCBEntry* curr = process.firstChild;
            while (curr!=NULL){
                curr = curr->nextChild;
                childrenNum++;
            }
            printf("# of children: |%d\n",childrenNum);
            // Time consumed
            printf("Time consumed: |%d\n",process.timeRanFor);
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
    procTable[1].func();
    
}



