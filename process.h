typedef struct Process {
   int PID;
   int timecreated;
   int memsize;
   int jobtime;
   int memaddr;
   int qtimeleft;
} process_t;  

process_t *createprocess(int PID, int timecreated, int jobtime, int memsize, int memaddr);