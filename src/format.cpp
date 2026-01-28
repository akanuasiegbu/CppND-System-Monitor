#include <string>
#include <sstream>
#include <iomanip>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    long hours = seconds/3600;
    long mins = (seconds % 3600) / 60;
    long secs = seconds % 60;

    std::ostringstream stream;

    stream << std::setfill('0') 
           << std::setw(2) << hours << ":" 
           << std::setw(2) << mins << ":" 
           << std::setw(2) << secs; 
    
    return stream.str();
}
