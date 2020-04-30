#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
#include "format.h"

#include <string>

using std::string;
using std::to_string;

string Format::ElapsedTime(long int times) {
  int hours = (times / seconds_per_hour) % hours_per_day;
  int minutes = (times % seconds_per_hour) / seconds_per_minute;
  int seconds = times % seconds_per_minute;

  std::string hh = hours >= 10 ? std::to_string(hours) : "0" + std::to_string(hours);
  std::string mm = minutes >= 10 ? std::to_string(minutes) : "0" + std::to_string(minutes);
  std::string ss = seconds >= 10 ? std::to_string(seconds) : "0" + std::to_string(seconds);

  return hh + ":" + mm + ":" + ss;
}