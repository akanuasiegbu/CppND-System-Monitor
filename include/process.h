#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
 // this Pid here seems like a getter, still need a setter
 // Also do I call setter everytime, how does that work with operator
 // I need to 
  int Pid();                               // TODO: See src/process.cpp - Done
  void Pid(int pid);                       //Created a setter           - Done
  std::string User();                      // TODO: See src/process.cpp - Done
  std::string Command();                   // TODO: See src/process.cpp - Done (Double check)
  float CpuUtilization();                  // TODO: See src/process.cpp - Done
  std::string Ram();                       // TODO: See src/process.cpp - Done
  long int UpTime();                       // TODO: See src/process.cpp - Done
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
   int pid_ {0};
 
};

#endif
