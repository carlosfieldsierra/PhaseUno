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
PCBEntry currentProccess;


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
typedef struct PriorityQueue {
    PCBEntry* one;
    PCBEntry* two;
    PCBEntry* three;
    PCBEntry* four;
    PCBEntry* five;
    PCBEntry* six;
    PCBEntry* seven;
} PriorityQueue;

PriorityQueue priorityQueue;



/* 
    Adds to the priority queue
*/
void pq_add(int pid){
    // Get process
    int slot = pid % MAXPROC;
    PCBEntry process = procTable[slot];
    // Get priority
    int priority = process.priority;

    PCBEntry* head;
    if (priority==1){
        if (priorityQueue.one==NULL){
            priorityQueue.one = &process;
            return;
        }
        head = priorityQueue.one;
    }

   else if (priority==2){
        if (priorityQueue.two==NULL){
            priorityQueue.two = &process;
            return;
        }
        head = priorityQueue.two;
        

    } else if (priority==3){
        if (priorityQueue.three==NULL){
            priorityQueue.three = &process;
            return;
        }
        head = priorityQueue.three;

    } else if (priority==4){
        if (priorityQueue.four==NULL){
            priorityQueue.four = &process;
            return;
        }
        head = priorityQueue.four;

    } else if (priority==5){
        if (priorityQueue.five==NULL){
            priorityQueue.five = &process;
            return;
        }
        head = priorityQueue.five;

    } else if (priority==6){
        if (priorityQueue.six==NULL){
            priorityQueue.six = &process;
            return;
        }
        head = priorityQueue.six;

    } else if (priority==7){
        if (priorityQueue.seven==NULL){
            priorityQueue.seven = &process;
            return;
        }
        head = priorityQueue.seven;

    }

    while (head->nextPQ!=NULL){
        head = head->nextPQ;
    }
    head->nextPQ = &process;
}

void pq_remove(int pid){

}

void pq_pushToEnd(int pid){

}

int pq_get(){
    return 0;
}

void pq_dump(){
    
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



void process_init_func(){
    // Create sentinel process
    PCBEntry sentinel;
    sentinel.pid = 2;
    sentinel.priority = 7;
    sentinel.status = READY;
    sentinel.parent = NULL;
    sentinel.firstChild = NULL;
    sentinel.nextChild = NULL;
    strcpy(sentinel.name,"sentinel");
    sentinel.func = sentinel_init_func;
    procTable[2 % MAXPROC] = sentinel;   
    pq_add(sentinel.pid);
     
    // Create testcase main process
    PCBEntry main;
    main.pid = 3;
    main.priority = 5;
    main.status = READY;
    main.parent = NULL;
    main.firstChild = NULL;
    main.nextChild = NULL;
    strcpy(main.name,"main");
    main.func = testcase_main;
    procTable[3 % MAXPROC] = main;   
    pq_add(main.pid);
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
    struct PCBEntry init;

    init.pid =1;
    init.priority = 1;
    init.status = READY;
    init.parent = NULL;
    init.firstChild = NULL;
    init.nextChild = NULL;
    strcpy(init.name,"init");
    init.func = process_init_func;
    procTable[1 % MAXPROC] = init;   
    pq_add(init.pid);

    return ;
}

int   fork1(char *name, int(*func)(char *), char *arg, int stacksize, int priority){
        
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
void  dumpProcesses(void){
    printf("---------------------------\n");
    for (int i=0;MAXPROC>i;i++){
        printf("---------------------------\n");
        if (procTable[i].pid == -1){
            printf("NULL");
        } else {
            printf("Name:          |%s\n",procTable[i].name);
            printf("PID:           |%d\n",procTable[i].pid);
            // Parent pid
            int parentPid = -1;
            if (procTable[i].parent != NULL){
                parentPid = procTable[i].parent->pid;
            }
            printf("Parent PID:    |%d\n",parentPid);
            // Priority
            printf("Priority:      |%d\n",procTable[i].priority);
            printf("status:        |%d\n",procTable[i].status);
            // # of children
            int childrenNum = 0;
            PCBEntry* curr = procTable[i].firstChild;
            while (curr!=NULL){
                curr = curr->nextChild;
                childrenNum++;
            }
            printf("# of children: |%d\n",childrenNum);
            // Time consumed
            printf("Time consumed: |%d\n",procTable[i].timeRanFor);
        }
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
    phase1_init();
   
    


    /* 
        Call the init process
    */
    procTable[1].func();
    
}



