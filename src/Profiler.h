/***************************************************
 * profiler.h
 * Created on Tue, 28 Mar 2023 10:55:27 +0000 by vladimir
 *
 * $Author$
 * $Rev$
 * $Date$
 ***************************************************/
#pragma once
#include <chrono>

class Profiler {
public:
  Profiler(size_t &storeTime);
  ~Profiler();

private:
  size_t &m_storeTime;
  std::chrono::high_resolution_clock::time_point m_start;
};
