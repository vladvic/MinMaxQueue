/***************************************************
 * MinMaxQueue.h
 * Created on Mon, 10 Apr 2023 10:43:52 +0000 by vladimir
 *
 * $Author$
 * $Rev$
 * $Date$
 ***************************************************/
#pragma once

#include <deque>
#include <utility>
#include <stdexcept>

template<typename T>
class MinMaxQueue {
public:
  template<typename M>
  void push(M e);
  T pop();

  bool empty() const;

  const T &min() const;
  const T &max() const;

private:
  typedef T *MinMaxElement;

  void update_min_max();

  std::deque<T> _queue;
  std::deque<MinMaxElement> _min_element;
  std::deque<MinMaxElement> _max_element;
};

template<typename T>
void MinMaxQueue<T>::update_min_max() {
  while (!_min_element.empty() && *_min_element.back() >= _queue.back()) {
    _min_element.pop_back();
  }
  _min_element.push_back(&_queue.back());
  while (!_max_element.empty() && *_max_element.back() <= _queue.back()) {
    _max_element.pop_back();
  }
  _max_element.push_back(&_queue.back());
}

template<typename T>
template<typename M>
void MinMaxQueue<T>::push(M e) {
  _queue.emplace_back(std::forward<T>(e));
  update_min_max();
}

template<typename T>
T MinMaxQueue<T>::pop() {
  if (empty()) {
    throw std::invalid_argument("Queue is empty!");
  }
  if (_min_element.front() == &_queue.front()) {
    _min_element.pop_front();
  }
  if (_max_element.front() == &_queue.front()) {
    _max_element.pop_front();
  }
  auto element = std::move(_queue.front());
  _queue.pop_front();
  return element;
}

template<typename T>
bool MinMaxQueue<T>::empty() const {
  return _queue.empty();
}

template<typename T>
const T &MinMaxQueue<T>::min() const {
  if (empty()) {
    throw std::invalid_argument("Queue is empty!");
  }

  return *_min_element.front();
}

template<typename T>
const T &MinMaxQueue<T>::max() const {
  if (empty()) {
    throw std::invalid_argument("Queue is empty!");
  }

  return *_max_element.front();
}

