// /* 
//     - Every function needs to disable and renable interrupts when it starts and end
//         -See the USLOSS documentation to see how to read and edit the PSR to
//          disable and restore interrupts
//         - Therefore, when you disable interrupts at the top of your function, save the
//             old PSR state, and make a point of restoring the PSR to exactly its previous
//             value before you return.



//     - Therefore, your code must check, at the top of each of the required functions
//         - print an error message and call USLOSS_Halt(1).



//     -  context switch
//         If the dispatcher performs a context switch, it must call mmu_switch(new_pid)
//         to notify the MMU that it needs to switch page tables. Note that you must do
//         this anytime that you call USLOSS_ContextSwitch() - even if you don’t have
//         an old context (such as during startProcesses()).

//     getAviablePid(){
//         while (proccesTable[slot]!=NILL){
//             curPid++;
//         }
//         return curPid
//     }




//     Questions?
//     - Where to update and remove from pq 

//     Notes 
//         - keep track of how zapped process so you can awaken during quit
// */

// #include <phase1.h>
// #include <usloss.h>
// #include <stdio.h>
// #include <string.h>

// //
// #define RUNNING 0                                                   /* max of one process can have this status */
// #define READY   1                                                   /* starting status of processes */
// // #define BLOCKED 2                                                   /* status of blocked process */
// #define ZAPPED  3                                                   /* status of zapped process, not yet quit */
// #define QUIT    4
// #define FINISHED 5
// // 10 > BLOCKED 
// #define UNUSED -1
// //

// /* 
//     Types
// */
// typedef void (*Process)();


// typedef struct PCBEntry {
//     int pid;
//     int priority;
//     int status; 
//     int isZapped;
//     // Keep track of when the shit started 
//     int timeSliceStart;
//     // Keep track of how long it ran for
//     int timeRanFor; 
//     struct PCBEntry* parent;
//     struct PCBEntry* firstChild;
//     struct PCBEntry* nextChild;
//     char procName[MAXNAME];
//     USLOSS_Context context;
//     Process func;
//     // Args 
//     char* args;

// } PCBEntry;


// // Update and remove
// // add
// //     - bootstrap phase
// //     - fork()
// // 
// // update 
// //   - bring blocked element to the end
// //   - run for  80ms then put back in the queue
// // 
// // Get
// //  - find the first ready element in the queue
// //  - remove from queue
// //  
// // - add(pid) -  add a procces to the class
// // - pushToEnd(pid) - takes the elemnt of the list
// // - pushToFront(pid) - takes the element and puts at head
// // - remove(pid) - removes element from queue
// typedef struct PriorityQueue {
//     PCBEntry* one;
//     PCBEntry* two;
//     PCBEntry* three;
//     PCBEntry* four;
//     PCBEntry* five;
//     PCBEntry* six;
//     PCBEntry* seven;
// }


// /* 
//     Fields
// */
// struct PCBEntry procTable[MAXPROC];

// int curPID = 1;
// PCBEntry currentProccess;



// void dispacther(){
//     // Find lowest prioity process

//     // Context switches 
//         // mmu_switch(new_pid)
//         // currentProccess.timeRanFor needs to updated to how long that process ran for
//         // switch(currentProccess.context,nextProcess.context);
//         // nextProcess.timeSlice = updated time;
//         // nextProcess.timeRanFor = 0;
//         // currProcess = nextProcess
//         // nextProcess.func(nextProcess.args);
//         // quit(nextProcess.pid);



// }


// /* 
//     Setup
// */
// void crearteInitProcces(){
//     //  createSentinelProc()

//     // createMainProc()

//     // While 1: 
//     //   int val = join(0);
//     //   if val == -2:
//     //        errorr message & halt
     
    
// }

// // void sentinelProc(){
// //         while (1) {
// //                 if (phase2_check_io() == 0){
// //                 //      report deadlock and terminate simulation
// //                 }
// //                 USLOSS_WaitInt();
// // }
// // }


// void createSentinelProc(){
//     return;
// }

// void createMainProc(){
//     return;
// }

// /* 
//     Creates sentinal and main process
// */
// void initProccess(){
//     PCBEntry mainProc;
//     // Set fields
//     curPID++;
//     mainProc.pid = curPID;
//     mainProc.priority = 6;
//     mainProc.parent = NULL;
//     mainProc.firstChild = NULL;
//     mainProc.nextChild = NULL;
//     strcpy( mainProc.procName, "main");
//     mainProc.func = crearteInitProcces;
    





//     return;
// }


// /* 
//     Creates the first process in the proc table
// */
// void  phase1_init(void){
//     PCBEntry initProc;
//     curPID = 1;
//     // Set fields
//     initProc.pid = 1;
//     initProc.priority = 6;
//     initProc.parent = NULL;
//     initProc.firstChild = NULL;
//     initProc.nextChild = NULL;
//     strcpy( initProc.procName, "init");
//     initProc.func = crearteInitProcces;
//     // Add to proc table
//     procTable[1 % MAXPROC] = initProccess;
//     // set to current process 
//     currentProccess = initProc;
//     // Call dispatcher
//     dispatcher();
// };



// int  fork1(char *name, int(*func)(char *), char *arg, int stacksize, int priority){
//     // Create the entry in the table
//             //     Almost at the end of fork1() - after you’ve fully initialized the process entry
//             // for the child - you must call mmu_init_proc(pid)
//     // set status to ready
//     // call the function
//     // make the memory
//     // dispatcher
// 	return 0;
// };





// /* 
//     Runnable, suspdened, dead
// */  
// int  join(int *status){
//     // Check if process has children
//     // Finds highest priority child to run 
//     // Then blocks the current process
//     // calls distapcher which run the child 

//     // ?? delete child when done in  process table


//     // *status -> status 
//     return 0; // pid of dead child
// };


// /* 
//     Any time that a process is terminated with quit(), you must call mmu_quit(pid)
//     to inform the MMU that it can free the page table for that process.7
// */
// void quit(int status){
//     // Change current procces to not be runnable

//     // If the parent’s process is already waiting in a join()
//        // child->parent->status == BLOCKED

//     // If the parent’s process is not yet waiting in a join()
//         // set proccess status to == QUIT

//     //     If, when this process dies, one or more processes are blocked trying to zap()
//     // this process, all of them will be awoken immediately

//     return;
// };

// // never un blocks a processs
// int   zap(int pid){
//     // Error handling
//         // if the caller attempts to zap itself, or to zap a non-existent process (including
//             // if pid == curPid 
//             // error message
//             // USLOSS_Halt(1)

//         // If  a process that is still in the process table but has terminated, zap() will print
//         // an error message and call USLOSS_Halt(1). 
//                 // if procTable[pid]-> status == FINISHED 
//                 // error message
//                 // USLOSS_Halt(1)

//         // If called on pid 1
//                 // error message
//                 // USLOSS_Halt(1)

    
//     // Current process gets blocked
            


    
//     return 0;
// };

// int   isZapped(void){
//     // currProcces->isZapped
//     return 0;
// };

// int   getpid(void){
//     // curProcces->pid
//     return 0;
// };

// void  dumpProcesses(void){
//     // Prints out the entire proc table with all the fields 
//     return;
// };

// int   blockMe(int block_status){
//     // if block_status < 10: 
//         // error message
//         // halt

//     // currProcess->status  = block_status;

//     // call dispatcher
//     // dispatcher();
//     return 0;
// };

// int   unblockProc(int pid){
//     //  If the indicated process was not blocked, does not exist, or is blocked
//     // on a status ≤ 10.
//         // return -2;

//     // if proces is trying to block itself 
//         // return -2 


//     // change the status of the proccess at the pid to READY
//     // Place the process at the end of the run queue at is priority

//     // dispatcher()
//     return 0;
// };

// int   readCurStartTime(void){
//     // currentProcces->timeSliceStart
//     return 0;
// };

// void  timeSlice(void){
//     //  if  80 < readtime():
//         // curProcess.status = READY;
//         // call pushToEnd(curProcces.pid) to put the process at the end of the queue ;
//         // dispatcher();


//     return;
// };

// // returns the total time (in microseconds)
// int   readtime(void){

//     /// return currentTime() -  currentProccess->timeSliceStart
//     return 0;
// };

// int   currentTime(void){
//     // return from this function USLOSS_DeviceInput(USLOSS_CLOCK_DEV, ...)
//     return 0;
// };

// void  startProcesses(void){
//     // calls the init process which makes all the data structures
//     // dispacther();
//     // 
// };