# COMP111 Project 2 README
## Scheduler Simulator Project


Matthew Carrington-Fair		mcarri01
Tomer Shapira				tshapi02
Justin Lee					tlee05

## Design Overview:

	List of Files:
			scheduler.c : File containing main
			simulator.c
			simulator.h
			FCFS.h
			FCFS.c
			CFS.h
			CFS.c
			param_structures.h
			Makefile


## Algorithm Choice:

	We chose to implement FCFS because it would provide a nice contrast to
	the CFS algorithm. With FCFS, through our input files we find that we 
	have 100% CPU usage because multiple processes are entering within a 
	similar time-frame (and in CFS we wait to add those until the next target latency if there are no other processes), however our average NTAT is higher than in CFS.

	In our FCFS implementation we would prioritize processes that were
	"first" in the input file containing the original list of processes
	in order to deal with multiple processes arriving at the same time.
	Each tick, we search through our list of processes (stored in order
	as they were given in the input file), and find any	processes that
	have an arrival time matching the given global time. Therefore, it
	would add processes to the run queue as they appear in the
	original waiting queue in stable order. 

## Approach to CFS Algorithm:

	We first made a queue to hold all of the processes that would be read in from a file. Every clock tick, we would check the queue for a process that had a run-time equal to the timeslice and add it to the "ready" queue. Each TL (time latency), we would check the "ready" queue and pop the processes within it into a RB tree. The RB tree would hold all of the processes to be run during a single TL. The RB tree would pick the process with the lowest virtual runtime and run it for the duration of the timeslice. 

	We chose a target latency of 10 because in our input files and tests we have at most 10 processes, we figure that within a given target latency we will probably have a couple processes (at most around 5) and so each process will be given a timeslice that is at least greater than a second (hopefully). With a target latency of 10 and testing with 10 processes, we believe that this puts the most "load" the scheduler can take where it can maintain reasonable timeslices for each process. If in some instance all 10 processes arrived at once, there would be potentially some processes with sub 1 second timeslices assuming that the priorities weren't the same for all processes. 

	In our implementation we floor each time-slice and subtract the current running time of a process to determine how much time a process has left to run within a single iteration. We then assume that if a process has less than 1 second left in its service time that it will finish before the next tick, therefore we to print that it finishes execution at the next tick and proceed with the next available process with the lowest virtual runtime. This "rounding down" of timeslices allows all processes that are present within our red black tree to run during a target latency. While these processes also execute at the appropriate time ticks on paper, it occasionally has the side-effect of shrinking actual run-time and leaving empty processor time at the end of a target latency. However, we believe that the output more accurately matches how each process should run within a target latency given its timeslice.


## Summary of Input Files:

	Our input files each contain 10 processes that have a wide range of arrival and service times. None of the processes run for more than 10 ticks, but they arrive anywhere from time 0 to 20, and priority values ranging from -20 to 19.

## Extra Credit:

	See CFS approach, used red-black tree to store processes that were available to run within a given time latency. 

## Additional Comments:

	DEFINE QUITTING/EXITING GRACEFULLY
