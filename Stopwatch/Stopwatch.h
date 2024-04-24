#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class Stopwatch
{
public:
  static Stopwatch& getInstance()
  {
    static Stopwatch instance;
    return instance;
  }

private:
  struct TimerData
  {
    std::string name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop;

    int64_t getMicros() const
    {
      return static_cast<int64_t>(std::chrono::duration_cast<std::chrono::microseconds>(
        stop - start).count());
    }
  };

public:
  size_t startTimer(const std::string& name)
  {
    TimerData d;
    d.name = name;
    d.start = std::chrono::high_resolution_clock::now();
    m_timers.push_back(d);
    return m_timers.size() - 1;
  }

  int64_t stopGetMicros(size_t id)
  {
    m_timers[id].stop = std::chrono::high_resolution_clock::now();
    return m_timers[id].getMicros();
  }

  void print(size_t id) const
  {
    std::cout << m_timers[id].name << ": " << m_timers[id].getMicros() << " us\n";
  }

  void printAll() const
  {
    for (size_t id = 0; id < m_timers.size(); id++)
      print(id);
  }

  void clear()
  {
    m_timers.clear();
  }

  std::vector<TimerData> m_timers;
};