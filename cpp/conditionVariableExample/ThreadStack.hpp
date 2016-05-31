#ifndef MY_THREAD_STACK_
#define MY_THREAD_STACK_

#include <mutex>
#include <condition_variable>

#include <vector>

template<class T>
class ThreadStack
{
  std::mutex mutex;
  std::condition_variable cvar;
  std::vector<T> data;
public:

  template<typename ConsumeFunction>
  void consumeBy(ConsumeFunction&& f) {
    std::unique_lock<std::mutex> lock(mutex);
    cvar.wait(lock, [this]{
	return !this->data.empty();
      });

    T dataChunk = std::move(data.back());
    data.pop_back();

    lock.unlock();
    f(dataChunk);
  }

  template<typename ProduceFunction>
  void produceFrom(ProduceFunction&& f) {
    std::lock_guard<std::mutex> lock(mutex);
    data.push_back(f());
    cvar.notify_one();
  }
};


#endif
