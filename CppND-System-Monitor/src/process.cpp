#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Create the constructor
Process::Process(int pid) : PID_(pid){}

// TODO: Return this process's ID
int Process::Pid() const { return PID_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const {
  float processJiffles = LinuxParser::ActiveJiffies(Pid());
  float processStartTime = Process::UpTime();
  float systemStartTime = LinuxParser::UpTime();    
  float elapsedTime = systemStartTime - (processStartTime / sysconf(_SC_CLK_TCK)); // The total elapsed time in seconds since the process started
    
  return (processJiffles / sysconf(_SC_CLK_TCK)) / elapsedTime;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Pid()); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Pid()); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() const { return LinuxParser::UpTime(Pid()); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return CpuUtilization() < a.CpuUtilization();
}