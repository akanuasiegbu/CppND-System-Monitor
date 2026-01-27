#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <assert.h>

#include "linux_parser.h"
// int LinuxParser::total_proc = 0;
// int LinuxParser::run_proc = 0;
using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  std::ifstream meminfo (kProcDirectory + kMeminfoFilename) ;
  // const std::string path = kProcDirectory + kMeminfoFilename;
  // std::ifstream meminfo(path) ;
  std::string line;
  std::string kword;
  float kb_amount;
  std::string kb;
  std::vector<float> mem;

  if (meminfo){
    while ( std::getline(meminfo, line))
    {
      // " " is for strings ' ' is for chars
      std::replace(line.begin(), line.end(), ':', ' ');

      std::istringstream sline(line);
      sline >> kword >> kb_amount >> kb;

      if (kword == "MemTotal" ||  kword == "MemFree" || kword  == "MemAvailable"){
        mem.push_back(kb_amount);
      }

    }
  }

  assert(mem.size() == 3);
  return (mem[0] - mem[1])/mem[0];
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  
  std::ifstream up_time(kProcDirectory + kUptimeFilename);
  long time;
  std::string line;
  
  if (up_time){
    while (std::getline(up_time, line))
    { 
      std::istringstream sline(line);

      sline >> time;

    }

  }
  
  return time; 
  }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

vector<int> LinuxParser::CpuUtilization(int pid) { 
  std::ifstream statinfo{kProcDirectory + std::to_string(pid) + kStatFilename};

  std::vector<int> pid_cpu_util;

  std::string data;
  std::string line;

  if (statinfo){
    std::getline(statinfo, line);
    std::istringstream sline(line);
    
    int i = 1; // 1 index
    while(sline >> data)
    {
      if (i >=14 && i <= 17){
        pid_cpu_util.push_back(std::stoi(data));
      }
      else if (i==22){
        pid_cpu_util.push_back(std::stoi(data));
      }
      i += 1;

    } 
  }
  return pid_cpu_util;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  std::ifstream stat(kProcDirectory+kStatFilename);
  std::string line;
  std::string kword;
  int num;
  int total_proc {0};
  
  if (stat){
    while(std::getline(stat, line))
    {
     std::istringstream sline(line);
     sline >> kword >> num;

     if (kword == "processes"){ total_proc=num;} 
    }

  }
  return total_proc;
  }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  std::ifstream stat(kProcDirectory+kStatFilename);
  std::string line;
  std::string kword;
  int num;
  int run_proc {0};
  
  if (stat){
    while(std::getline(stat, line))
    {
     std::istringstream sline(line);
     sline >> kword >> num;

     if (kword == "procs_running"){ run_proc=num;} 
    }

  }

  return run_proc;
  }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::ifstream commandIn{kProcDirectory+std::to_string(pid) + kCmdlineFilename};

  std::string line;

  std::getline(commandIn, line);
  
  return line; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  std::ifstream statusinfo {kProcDirectory + std::to_string(pid) + kStatusFilename};
  std::string line;
  std::string kword;
  std::string second;
  std::string mem;

  if (statusinfo){
    while(std::getline(statusinfo, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream sline(line);
      sline >> kword >> second;

      if (kword == "VmSize") {mem = second;}
    }
  }
  
  return mem; 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  std::ifstream Userinfo {kProcDirectory + std::to_string(pid) + kStatusFilename};
  std::string line;
  std::string kword;
  std::string UserId;
  if (Userinfo){
    while(std::getline(Userinfo, line))
    {
      std::istringstream sline(line);
      sline >> kword >> UserId;
    }
  }

  
  return UserId; 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  std::string UserId = LinuxParser::Uid(pid);

  std::ifstream passwdInfo {kPasswordPath};
  std::string username;
  std::string line;
  std::string kword;
  char x;
  std::string FoundUserId;

  if (passwdInfo){
    while (std::getline(passwdInfo, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');

      std::istringstream sline(line);

      sline >> kword >> x >> FoundUserId;

      if (FoundUserId == UserId){ username = kword;}
      

    }
  }
  
  return username;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(int pid) { 

  std::ifstream up_time {kProcDirectory + std::to_string(pid) + kStatFilename};
  std::string line;
  
  std::getline(up_time, line);
  std::string token;
  std::istringstream sline(line);

  if (up_time){
    for (int i=0; i< 21; i++)
    {
      sline >> token;
    }

  }

  long time;
  sline >> time;


  return time/sysconf(_SC_CLK_TCK);
}
