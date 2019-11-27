#ifndef MY_RuleOfFiveBehaviourLogger_HPP
#define MY_RuleOfFiveBehaviourLogger_HPP

#include <iostream>
#include <memory>

#include "ICounter.hpp"

// #define DEBUG_PRINT

struct RuleOfFiveBehaviourLogger {
  std::shared_ptr<ICounter> counter;
  std::size_t id;

  RuleOfFiveBehaviourLogger(std::shared_ptr<ICounter> counter_)
    : counter(std::move(counter_)), id(counter->count()) {
    counter->inc();

#ifdef DEBUG_PRINT
    std::cout << "I am created [" << id << "]" << std::endl;
#endif
  }

  RuleOfFiveBehaviourLogger(RuleOfFiveBehaviourLogger&& other) noexcept
    : counter(other.counter), id(other.id) {

#ifdef DEBUG_PRINT
    std::cout << "I am moved [" << id << "]" << std::endl;
#endif
  }

  RuleOfFiveBehaviourLogger(const RuleOfFiveBehaviourLogger& other)
    : counter(other.counter), id(other.id) {

    counter->inc();

#ifdef DEBUG_PRINT
    std::cout << "I am copied [" << id << "]" << std::endl;
#endif
  }

  RuleOfFiveBehaviourLogger& operator= (const RuleOfFiveBehaviourLogger& other) {
    counter = other.counter;
    id = other.id;

    counter->inc();

#ifdef DEBUG_PRINT
    std::cout << "I am copy-assigned [" << id << "]" << std::endl;
#endif
    return *this;
  }

  RuleOfFiveBehaviourLogger& operator= (RuleOfFiveBehaviourLogger&& other) noexcept {
    counter = other.counter;
    id = other.id;

#ifdef DEBUG_PRINT
    std::cout << "I am copy-moved [" << id << "]" << std::endl;
#endif
    return *this;
  }

  ~RuleOfFiveBehaviourLogger() {
#ifdef DEBUG_PRINT
    std::cout << "I am destroyed [" << id << "]" << std::endl;
#endif
  }
};

std::ostream& operator<< (std::ostream& os, const RuleOfFiveBehaviourLogger& l) {
  return os << l.id;
}

#endif // MY_RuleOfFiveBehaviourLogger_HPP
