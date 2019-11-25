#include <stdexcept>
#include <limits>

#include "Counter.hpp"

void Counter::inc() {
  if (counter == std::numeric_limits<std::size_t>::max())
    throw std::logic_error("Counter overflow");

  counter++;
}

void Counter::dec() {
  if (counter == 0)
    throw std::logic_error("Zero counter decriment");

  counter--;
}

std::size_t Counter::count() const {
  return counter;
}
