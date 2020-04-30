#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  std::vector<std::string> JiffiesList = LinuxParser::CpuUtilization();
  
  for (size_t i = 0; i<JiffiesList.size();i++){
    if (i!=LinuxParser::kGuest_ && i!=LinuxParser::kGuestNice_){
      totalJiffies += std::stof(JiffiesList[i]);
    }
    if (i==LinuxParser::kIdle_ || i==LinuxParser::kIOwait_){
      idleJiffies += std::stof(JiffiesList[i]);
    }
  }
  activeJiffies = totalJiffies - idleJiffies;
  
  usage = (activeJiffies - activeJiffiesPrev)/(totalJiffies-totalJiffiesPrev);
  totalJiffiesPrev = totalJiffies;
  activeJiffiesPrev = activeJiffies;
 
  return usage; 
}