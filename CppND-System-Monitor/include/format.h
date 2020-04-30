#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format {
  std::string ElapsedTime(long times);  // DONE: See src/format.cpp
  static const int seconds_per_hour = 3600;
  static const int seconds_per_minute = 60;
  static const int hours_per_day = 24;
};                                    // namespace Format

#endif