#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

//  I added this to use name same const
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
/*You need to complete the mentioned TODOs in order to satisfy the rubric criteria "The student will be able to extract and display basic data about the system."

You need to properly format the uptime. Refer to the comments mentioned in format. cpp for formatting the uptime.*/

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    processes_.clear();

    std::vector<int>  pids = LinuxParser::Pids() ;
    int pid;
    while (pids.size() != 0){

        // Get Pid 
        pid = pids.back();
        pids.pop_back();

        // Create Process
        Process p1;
        p1.Pid(pid);

        //Adds the process 
        processes_.push_back(p1);
    }
    return processes_; 
    
    }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    std::string k_name {LinuxParser::Kernel()};

    return k_name; 
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    float mem_util {LinuxParser::MemoryUtilization()};
    
    return mem_util; 
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    std::string opsys {LinuxParser::OperatingSystem()};
   
    return opsys; 
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    int run_proc{LinuxParser::RunningProcesses()};
    return run_proc; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    // could maybe move into another function or make private member for speed
    // when understand more how Running Processing and total are connected
    // int num_processes {static_cast<int>(LinuxParser::Pids().size())};
    // // int num_processes = LinuxParser::Pids().size();
    // return num_processes;

    int num_processes {LinuxParser::TotalProcesses()};

    return num_processes;
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    long int time{LinuxParser::UpTime()};
    
    return time; }
