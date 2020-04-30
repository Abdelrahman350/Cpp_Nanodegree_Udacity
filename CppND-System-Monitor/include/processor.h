#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include "linux_parser.h"
#include <string>
#include <vector>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  // TODO: Declare any necessary private members
 private:
  float totalJiffies{0.0}, totalJiffiesPrev{0.0}, idleJiffies{0.0}, activeJiffies{0.0}, activeJiffiesPrev{0.0}, usage{0.0};
};

#endif