#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <assert.h>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid(){ 
    return this->pid_;
}

Process::Process(int pid): pid_(pid), username_(LinuxParser::User(pid)){};

// void Process::Pid(int pid){
//     pid_ = pid;
// }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    std::vector<int> pid_cpu_util {LinuxParser::CpuUtilization(Pid())};
    if (pid_cpu_util.size()< 3) return 0.0;
    
    // utime [0], stime[1], cutime[2], cstime[3], starttime [4]

    float hertz = sysconf(_SC_CLK_TCK);
    //total_time = utime + stime +cutime + cstime

    int total_time {0};
    for (int i =0; i < 4; i++)
    {
        total_time +=  pid_cpu_util[i];
    }

    float seconds  {static_cast<float>(LinuxParser::UpTime())- (static_cast<float>(pid_cpu_util[4])/hertz)};

    float cpu_usage {   100.0f*(static_cast<float>(total_time)/hertz)/seconds };
    
    return cpu_usage;
}


// TODO: Return the command that generated this process
string Process::Command() { 
    std::string pid_com {LinuxParser::Command(Pid())};
    return pid_com;
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    std::string Vmsize {LinuxParser::Ram(Pid())};
    
    return Vmsize; 
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    // username_ = LinuxParser::User(Pid());
    
    return username_; 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    long int up_time {LinuxParser::UpTime(Pid())};
    // this->up_time = LinuxParser::UpTime(Pid());

    return up_time; 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
    // Made pid_ and username_ const so can use
    // When mad pid_ and username_ const could not sort

    // Since per class access a can access private members
    return pid_ > a.pid_; // Using Pid to sort
    // return username_ > a.username_;
}
