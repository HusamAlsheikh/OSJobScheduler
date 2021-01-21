# OSJobScheduler
OS Job Scheduler for CIS 450. Program simulates Round Robin Scheduling on a single-CPU system.

## Overview:
This programming assignment is designed primarily to improve your understanding of a typical process scheduling algorithm. It also incoporates skills and knowledge that you have earned in previous classes, in particular, CIS200 Computer Science II and CIS350/3501 Data Structures.  

In this programming project you will study the behavior of the Round Robin Scheduling on a single-CPU system. One parameter that affects the performance of Round Robin policy is the time quantum. Using the simulation program you are about to develop, this effect can be easily observed by specifying different quantum each time the simulation is run.  

Recall that the execution of a process/job follows an alternating cycle of its CPU bursts and I/O bursts. In a system with a round-robin scheduler, the CPU bursts may be shorter or longer than the scheduler's time quantum.  

## Specifications:
1. The program that you are about to write is not a system program, it is just a typical user application that requires no spawning of processes, no timer interrupt handling, no I/O interrupt handling, etc. You are simulating a system program.  
2. This is an individual project, and implementation of the simulation program can be in any language of your choice  
3. Your program must use some form of "visual presentation" to show, at least, the following four components:  
  - A CPU  
  - A ready queue showing all the processes waiting to be dispatched to use the CPU  
  - An I/O device  
  - An I/O queue showing all the processes waiting to use the I/O device  
Your choice of "visual presentation" will be a text-mode to an output file (user will enter the name of the output file as first command-line input parameter) and the text-mode or GUI program implemented using any UI framework of your to the screen (you must provide screenshots of the execution of the program).  
4. The description of a simulated process includes the following information:  
  - Arrival time (ta) of the process  
  - Number of CPU bursts (N)  
  - CPU burst durations (ci, i = 1, 2, ..., N), I/O burst durations (dj, j = 1, 2, ..., N-1)
written in one line of the input file (the name of the input file will be entered by the user as second command-line input parameter) in the following order:
ta N c1 d1 c2 d2 ... cN-1 dN-1 cN
Recall that the execution of a process always begins and ends with a CPU burst. You can assume all the numbers are integers.  

What will you do if the format is incorrect number of values N=6 but 5 or 7 numbers? You must provide several test cases for this!  
5. An integer counter will simulate the system clock – there will be an output log file (the name of the log file will be entered by the user as third command-line input parameter). Every time unit in your simulation will be listed in this file along with what event(s) took place at that time. Every 5 time units (5, 10, 15, …) also display the current contents of the Ready Queue and I/O Queue (before events at that time begin).
6. Time quantum (integer) used in the Round Robin simulation is given as the fourth command-line input parameter.
7. The simulator shall print an appropriate message when a simulated process changes its state. Use the 5-state model (New, Ready, Running, Blocked, Exit). For instance, it shall print a message when it performs one of the following actions:
  - Starts a new process
  - Schedules a process to run
  - Moves a process to the I/O Waiting (Blocked) State
  - Preempts a process from the Running State
  - Moves a process back into the Ready State (due to I/O completion)
  - Starts servicing a process' I/O request  
Each message is prefixed with the current simulation time.  
8. When a simulated process is interrupted (because its current CPU burst is longer than the quantum) the process is preempted and re-enter the ready queue
9. When a simulated process completes its current CPU burst, it will then use its I/O burst, the simulator changes the process' state to Blocked. At this point, the CPU becomes idle and the dispatcher may select another process from the ready queues.
10. The simulated system has only one CPU and one I/O device. The I/O request of a process will be performed only if the I/O device is available. Otherwise, the process requesting the I/O operation will have to wait until the device is available. I/O is handled by the simulated device on first-come-first-serve basis.
11. Upon completion of its I/O burst, a process will change from Blocked state to Ready and join the Ready Queue again.
12. A process entering the ready queue can be one of the following:
  - a new process,
  - a process returning from Blocked state, or
  - a process preempted from the CPU  
When these three events happen at the same time, the new process will enter the Ready Queue first, followed by process returning from Blocked state, and finally by the preempted process.  
13.	When a simulated process terminates, the simulator then outputs a statement of the form:
14.	Job %d terminated: Turn Around Time = %d, Wait time = %d, I/O wait = %d
where " Turn Around Time " is total elapsed time, "Wait time" is the total time spent by a process in the Ready Queue, and "I/O wait" is the total amount of time the process had to wait for the I/O device.
15.	At the end of simulation, the simulator shall display the percentage of CPU utilization, average Turn Around Time, average wait time, and average I/O wait time.

### Sample Input File:
3 3 2 5 8 7 4  
5 1 4  
6 4 8 2 10 2 7 5 6  

This file represents three processes with the following execution behavior (pay attention to the order of CPU bursts and I/O bursts in the above input and the table below).  
Job | Arrival Time | CPU bursts | I/O bursts
----|--------------|------------|-----------
1 | 3 |2, 8, 4 | 5, 7
2 | 5 | 4 | -
3 | 6 | 8, 10, 7, 6 | 2, 2, 5

Please note the following:  
- Each process always starts and ends with a CPU burst.  
- The jobs in the input file are sorted in ascending order by their arrival time  

### Required Test Cases (you are required to validate the data results below are correct and create more tests!):  
Input File - CPU intensive jobs  
3 3 2 5 8 7 4  
5 1 4  
6 4 8 2 10 2 7 5 6  
Output File - Simulation Results  
Results for quantum = 3 CPU utilization = 84%  
P0 (TAT = 36, ReadyWait = 10, I/O-wait=0)  
P1 (TAT = 7, ReadyWait = 3, I/O-wait=0)  
P2 (TAT = 52, ReadyWait = 12, I/O-wait=0)  

Input File - I/O intensive jobs  
3 3 2 5 2 7 4  
5 2 1 10 2  
6 4 1 15 1 12 4 8 6  
Output File - Simulation Results  
Results for quantum = 2 CPU utilization = 32%  
P0 (Turn Around Time = 43, ReadyWait = 0, I/O-wait=23)  
P1 (Turn Around Time = 17, ReadyWait = 0, I/O-wait=4)  
P2 (Turn Around Time = 66, ReadyWait = 0, I/O-wait=19)  

Input File – Mixed jobs  
3 3 2 5 8 7 4  
4 1 4  
6 3 2 5 2 7 4  
8 4 8 2 10 2 7 5 6  
10 2 1 10 2  
13 4 1 15 1 12 4 8 6  
Output File - Simulation Results  
Results for quantum = 2 CPU utilization = 77%  
P0 (Turn Around Time = 60, ReadyWait = 18, I/O-wait=16)  
P1 (Turn Around Time = 7, ReadyWait = 3, I/O-wait=0)  
P2 (Turn Around Time = 47, ReadyWait = 7, I/O-wait=20)  
P3 (Turn Around Time = 86, ReadyWait = 24, I/O-wait=22)  
P4 (Turn Around Time = 19, ReadyWait = 5, I/O-wait=1)  
P5 (Turn Around Time = 75, ReadyWait = 7, I/O-wait=21)  

How might these change with different quantum times? (You will be reporting out on this! See turn-n section below)  

Invalid Input Examples  
0 2 5 2 2   < invalid start time; start time must be > 0; start time input = 0  
2 0 2 1 4   < invalid number of CPU bursts; must be > 0; number of CPU bursts = 0   
4 2 3 4      < number of CPU bursts = 2; number of CPU bursts input = 1  
6 3 0 6 1   < CPU burst or i/o burst value must be > 0; CPU or I/O burst value = 0  

Are there other errors?  

## Implementation Guidelines for Algorithm:
- Simulated Process and Data Structures
  - A process in your simulation program is just an "object" that your program manipulates.
  - You may have to design a data structure as a simplified representation of a typical PCB (Process Control Block). All the PCBs can be stored into an array-list, a dynamically allocated array, or other similar structures. In addition you may need to implement two queues to simulate the "ready queue" and the "I/O queue". If, for instance, you decide to use an arraylist to store the PCBs, the "ready queue" can simply be implemented as a linked list of integers, each integer is a "process ID" that can be used to index the arraylist.
- Discrete-Event Simulation
  - The kind of simulation that you will implement in this project is known as Discrete-Event Simulation. In our case, the discrete events are:
    - Arrival of a new job
    - Preemption of the current job from the CPU
    - Blocking of a job due to its I/O request
    - Completion of a job's I/O operation
    - Termination of a job
  - In a Discrete-Event Simulation, any event in the simulation will cause the state of the system changes at discrete time. These state transitions take place in simulated time (instead of real time).
- List of Discrete Events
  - The simulation loop of your program is driven by the list of (future) events in the system being simulated. In order to process all these events in a chonological order, they must be maintained in ascending order of their time of occurence. A heap or a priority queue is perhaps the best data structure for this list (you should have covered these in CIS 200 and/or CIS 350/3501). The simulation loop then removes one event at a time (starting from the earliest), changes the state of the system accordingly, and performs all the updates that must take place during the current simulation time.
  - The main loop of the simulation will probably look like the code on the last page
  - At the beginning of the simulation, only the job arrival events are known (from the input file), and these events can be immediately enqueued into the event list (only the events are created, the jobs themselves are not created at this point). The other four kinds of event cannot be determined yet, but they will be determined (generated) and inserted into the event list as the simulation progresses in time.

## Generating Future Events:  
How are future events determined?   

When a process is dispatched to use the CPU. There are three possible future events that may take place with respect to the process: PREEMPTION, IO_REQUEST, or TERMINATION. However, only one of these future events will take place depending on the scheduler quantum time, the process current CPU burst, and whether this process has an I/O burst following the current CPU burst.  

As an example, Job 1 in the sample input above. Assume that the system quantum time is 3 units.
- When Job1 is dispatched at time T to run its first CPU burst, the next (future) event for Job1 must be IO_REQUEST that will take place at time T+2, i.e. the current time + the remaining CPU burst. At thist point a new IO_REQUEST event must be inserted into the event list. Job1 itself, however, will not be blocked at the current simulation time. Later at time T+2, when the simulation loop handles the IO_REQUEST event, Job1 will be moved from the CPU to the I/O queue.
- When later Job1 is dispatched at time U to run its second CPU burst, the next (future) event for Job1 must be PREEMPTION that will take place at time U+3, i.e. the current time + the system quantum. Likewise, a new PREEMPTION event will be inserted into the event list and the actual preemption will take place later when the simulation loop is at time U+3 handlilng the PREEMPTION event.
Other future events will be generated using a similar technique.  

## Event Structure:  
If you implement the simulation program in C++, an "Event" is perhaps a structure that may look like the following:  

struct eventNode   
 {   
   int time;                /* when the event will occur */  
   int type;                /* type of event */  
   int process_id;      /* to whom this event applies */  
  };  

eventNode event;  


What would your Process Control Block structure look like?  

