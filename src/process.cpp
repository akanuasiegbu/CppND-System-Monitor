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


    const float hertz = sysconf(_SC_CLK_TCK);
    const float cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
    

    long total_jiff {LinuxParser::ActiveJiffies(Pid())};
    float uptime = static_cast<float>(LinuxParser::UpTime());
    long startime {0};

    std::ifstream statinfo{LinuxParser::kProcDirectory + std::to_string(Pid()) + LinuxParser::kStatFilename};
      if (statinfo){
        std::string data;
        std::string line;
        std::getline(statinfo, line);

        auto rparen = line.rfind(')');

        std::istringstream sline(line.substr(rparen + 2));

        int i = 3; 
        while(sline >> data)
        {
            if (i==22){
                startime = std::stof(data);
            
            }

            i += 1;

        } 

    }

    float seconds = uptime - (startime/hertz);

    if (seconds <= 0.0f) return 0.0f;

    return (100.0f*(static_cast<float>(total_jiff)/hertz)/seconds)/cpu_count;
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
