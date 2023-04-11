/***************************************************
 * Profiler.cpp
 * Created on Mon, 10 Apr 2023 19:36:37 +0000 by vladimir
 *
 * $Author$
 * $Rev$
 * $Date$
 ***************************************************/

#include "Profiler.h"

using namespace std::chrono;

Profiler::Profiler(size_t &storeTime) 
  : m_storeTime(storeTime)
  , m_start(high_resolution_clock::now())
{ }

Profiler::~Profiler() {
  m_storeTime = duration_cast<nanoseconds>(high_resolution_clock::now() - m_start).count();
}
