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

    void start()
    {
      m_micros += static_cast<int64_t>(std::chrono::duration_cast<std::chrono::microseconds>(
        m_stop - m_start).count());
      m_start = std::chrono::high_resolution_clock::now();
      m_stop = m_start;
    }

    void stop()
    {
      m_stop = std::chrono::high_resolution_clock::now();
      m_micros += static_cast<int64_t>(std::chrono::duration_cast<std::chrono::microseconds>(
        m_stop - m_start).count());
      m_start = m_stop;
    }

    int64_t getMicros() const
    {
      return m_micros;
    }

  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_stop;
    size_t m_micros{ 0 };
  };

public:

  // Add and start new timer.
  size_t start(const std::string& name)
  {
    TimerData d;
    d.name = name;
    d.start();
    m_timers.push_back(d);
    return m_timers.size() - 1;
  }

  // Start already existing timer.
  void start(size_t id)
  {
    m_timers[id].start();
  }

  int64_t stopGetMicros(size_t id)
  {
    m_timers[id].stop();
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