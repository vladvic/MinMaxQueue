/***************************************************
 * test.cpp
 * Created on Mon, 10 Apr 2023 11:42:45 +0000 by vladimir
 *
 * $Author$
 * $Rev$
 * $Date$
 ***************************************************/

#include <gtest/gtest.h>
#include <map>
#include "MinMaxQueue.h"
#include "Profiler.h"

using namespace std;

class MinMaxQueueTest 
  : public ::testing::Test
{
protected:
  MinMaxQueue<int> queue;
};

TEST_F(MinMaxQueueTest, PushElements) {
  ASSERT_TRUE(queue.empty()) << "queue should be empty";

  ASSERT_THROW(queue.pop(), std::invalid_argument) << "max should throw";
  ASSERT_THROW(queue.min(), std::invalid_argument) << "min should throw";
  ASSERT_THROW(queue.max(), std::invalid_argument) << "max should throw";

  queue.push(1); // min: 1; max: 1
  ASSERT_EQ(queue.min(), 1) << "min should be 1";
  ASSERT_EQ(queue.max(), 1) << "max should be 1";

  queue.push(2); // min: 1; max: 2
  ASSERT_EQ(queue.min(), 1) << "min should be 1";
  ASSERT_EQ(queue.max(), 2) << "max should be 2";

  queue.push(-1); // min: -1; max: 3
  ASSERT_EQ(queue.min(), -1) << "min should be -1";
  ASSERT_EQ(queue.max(), 2) << "max should be 2";

  queue.push(3); // min: 1; max: 3
  ASSERT_EQ(queue.min(), -1) << "min should be -1";
  ASSERT_EQ(queue.max(), 3) << "max should be 3";

  ASSERT_FALSE(queue.empty()) << "queue should be empty";
}

TEST_F(MinMaxQueueTest, PopElements) {
  // Prepare pop test
  queue.push(1);
  queue.push(2);
  queue.push(-1);
  queue.push(3);

  ASSERT_FALSE(queue.empty()) << "queue should be empty";

  ASSERT_EQ(queue.pop(), 1) << "popped result should be 1";
  ASSERT_EQ(queue.min(), -1) << "min should be -1";
  ASSERT_EQ(queue.max(), 3) << "max should be 3";

  ASSERT_EQ(queue.pop(), 2) << "popped result should be 2";
  ASSERT_EQ(queue.min(), -1) << "min should be -1";
  ASSERT_EQ(queue.max(), 3) << "max should be 3";

  ASSERT_EQ(queue.pop(), -1) << "popped result should be -1";
  ASSERT_EQ(queue.min(), 3) << "min should be 3";
  ASSERT_EQ(queue.max(), 3) << "max should be 3";

  ASSERT_EQ(queue.pop(), 3) << "popped result should be 3";

  ASSERT_THROW(queue.min(), std::invalid_argument) << "min should throw";
  ASSERT_THROW(queue.max(), std::invalid_argument) << "max should throw";
  ASSERT_THROW(queue.pop(), std::invalid_argument) << "max should throw";

  ASSERT_TRUE(queue.empty()) << "queue should be empty";
}

TEST_F(MinMaxQueueTest, PushPopMix) {
  queue.push(1); // min: 1; max: 1
  ASSERT_EQ(queue.min(), 1) << "min should be 1";
  ASSERT_EQ(queue.max(), 1) << "max should be 1";

  queue.push(2); // min: 1; max: 2
  ASSERT_EQ(queue.min(), 1) << "min should be 1";
  ASSERT_EQ(queue.max(), 2) << "max should be 2";

  ASSERT_EQ(queue.pop(), 1) << "popped result should be 1";
  ASSERT_EQ(queue.min(), 2) << "min should be 2";
  ASSERT_EQ(queue.max(), 2) << "max should be 2";

  queue.push(-2); // min: -2; max: 2
  ASSERT_EQ(queue.min(), -2) << "min should be -2";
  ASSERT_EQ(queue.max(), 2) << "max should be 2";

  ASSERT_EQ(queue.pop(),  2) << "popped result should be 2";
  ASSERT_EQ(queue.min(), -2) << "min should be -2";
  ASSERT_EQ(queue.max(), -2) << "max should be -2";

  ASSERT_EQ(queue.pop(),  -2) << "popped result should be -2";
  ASSERT_THROW(queue.min(), std::invalid_argument) << "min should throw";
  ASSERT_THROW(queue.max(), std::invalid_argument) << "max should throw";

  ASSERT_TRUE(queue.empty()) << "queue should be empty";
}

TEST_F(MinMaxQueueTest, PushPopTime) {
  constexpr size_t nRepeats[2] = {10000, 100000};
  size_t elapsedPushTime, elapsedPopTime, elapsedMinMaxTime;

  // Push/min/max/pop nRepeats[0] times
  {
  Profiler prof(elapsedPushTime);

  for (size_t i = 0; i < nRepeats[0]; ++ i) {
    queue.push(i%4);
  }

  }

  {
  Profiler prof(elapsedMinMaxTime);

  for (size_t i = 0; i < nRepeats[0]; ++ i) {
    ASSERT_EQ(queue.min(), 0) << "min should be 0";
    ASSERT_EQ(queue.max(), 3) << "max should be 3";
  }

  }

  {
  Profiler prof(elapsedPopTime);

  while(!queue.empty()) {
    queue.pop();
  }

  }

  size_t newElapsedPushTime, newElapsedPopTime, newElapsedMinMaxTime;

  // Push/min/max/pop nRepeats[1] times
  {
  Profiler prof(newElapsedPushTime);

  for (size_t i = 0; i < nRepeats[1]; ++ i) {
    queue.push(i%4);
  }

  }

  {
  Profiler prof(newElapsedMinMaxTime);

  for (size_t i = 0; i < nRepeats[1]; ++ i) {
    ASSERT_EQ(queue.min(), 0) << "min should be 0";
    ASSERT_EQ(queue.max(), 3) << "max should be 3";
  }

  }


  {
  Profiler prof(newElapsedPopTime);

  while(!queue.empty()) {
    queue.pop();
  }

  }

  ASSERT_LE(newElapsedPushTime / elapsedPushTime, 1 + nRepeats[1] / nRepeats[0]) << "operations should take amortized constant time";
  ASSERT_LE(newElapsedPopTime / elapsedPopTime, 1 + nRepeats[1] / nRepeats[0]) << "operations should take amortized constant time";
  ASSERT_LE(newElapsedMinMaxTime / elapsedMinMaxTime, nRepeats[1] / nRepeats[0]) << "operations should take constant time";
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
