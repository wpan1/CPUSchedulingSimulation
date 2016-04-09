# CPUSchedulingSimulation
Simulates FCFS and a basic Multi-level feedback queue

1. First-come first-served queue: The queue simply contains a list of all processes to be scheduled.
The queue type corresponds to a non-preemptive algorithm. That is, once a process begins
executing it continues executing until the total running time elapsed reaches the specified jobtime.
2. Multi-level feedback queue: A simplified three-level round robin multi-level feedback queue
contains a list of all process to be scheduled.
  * New processes are added to queue Q1 with quantum = 2.
  * After exhausting their quantum, if additional CPU time is required the process is subsequently moved to queue Q2 with quantum = 4.
  * If a process requires additional CPU time, it is moved to the final queue Q3 with quantum = 8.
The round robin mechanism is then used for scheduling until all processes have terminated.

The name of the process data file should be specified at run time using a ‘-f’ filename option. The
scheduling algorithm to be used should be specified using the ‘-a’ algorithm name option, where algorithm
name is one of fcfs, multi corresponding to the first come first served and multi-level feedback
queue respectively. The size of main memory should be specified using the ‘-m’ memsize option, where
memsize is an integer.
A sample command line:
./simulation -f in.txt -a fcfs -m 200 > out.txt
