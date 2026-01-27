#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();                   // TODO: See src/system.cpp
  std::vector<Process>& Processes();  // TODO: See src/system.cpp - Done
  float MemoryUtilization();          // TODO: See src/system.cpp - Done
  long UpTime();                      // TODO: See src/system.cpp - Done
  int TotalProcesses();               // TODO: See src/system.cpp - Done
  int RunningProcesses();             // TODO: See src/system.cpp - Done
  std::string Kernel();               // TODO: See src/system.cpp - Done
  std::string OperatingSystem();      // TODO: See src/system.cpp - Done

  // TODO: Define any necessary private members
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
};

#endif
