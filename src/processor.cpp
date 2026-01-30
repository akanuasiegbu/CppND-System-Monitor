#include "processor.h"
#include "linux_parser.h"
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {

    if (prevActive ==-1 || prevIdle== -1){
        prevActive = LinuxParser::ActiveJiffies();
        prevIdle   = LinuxParser::IdleJiffies();
    }

    long active = LinuxParser::ActiveJiffies();
    long idle   = LinuxParser::IdleJiffies();
    
    
    long prevTotal = prevActive + prevIdle;
    long total = active + idle;

    // diff

    long totald = total - prevTotal;
    long idled =  idle - prevIdle;

    prevActive = active;
    prevIdle = idle;

    return static_cast<float>(totald - idled)/ static_cast<float>(totald);

}
