#ifndef MY_ICOUNTER_HPP
#define MY_ICOUNTER_HPP

struct ICounter {
  virtual ~ICounter() = default;

  virtual void inc() = 0;
  virtual void dec() = 0;

  virtual std::size_t count() const = 0;
};

#endif // MY_ICOUNTER_HPP
