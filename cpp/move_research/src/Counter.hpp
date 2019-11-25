#ifndef MY_COUNTER_HPP
#define MY_COUNTER_HPP

#include <atomic>

#include "ICounter.hpp"

struct Counter : public ICounter {
  virtual ~Counter() = default;

  virtual void inc() override final;
  virtual void dec() override final;

  virtual std::size_t count() const override final;

private:
  std::atomic<std::size_t> counter = 0;
};

#endif // MY_COUNTER_HPP
