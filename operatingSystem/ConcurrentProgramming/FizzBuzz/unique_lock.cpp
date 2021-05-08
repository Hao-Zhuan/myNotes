#include "fizzbuzz.hpp"
#include <mutex>
class U_lock : public myFizzBuzz //mutex+RAII
{
  std::mutex mtFizzBuzz, mtFizz, mtBuzz;
  std::unique_lock<std::mutex> lock_FB, lock_F, lock_B;

public:
  U_lock(int n)
      : myFizzBuzz(n),
        lock_FB(mtFizzBuzz, std::try_to_lock),
        lock_F(mtFizz, std::try_to_lock),
        lock_B(mtBuzz, std::try_to_lock) {}

  ~U_lock() = default;
  void init()
  {
    
  }
  void FizzBuzz(std::function<void()> printFizzBuzz)
  {
    if (count > n)
      return;
    if (count % 15 == 0)
    {
      printFizzBuzz();
      count++;
      init();
    }
    else
      mtFizzBuzz.unlock();
  }
  void Fizz(std::function<void()> printFizz)
  {
    if (count > n)
      return;
    if (count % 3 == 0)
    {

      printFizz();
      count++;

      init();
    }
    std::lock_guard<std::mutex> guard(mtFizzBuzz);
    lock_F.unlock();
  }
  void Buzz(std::function<void()> printBuzz)
  {
    if (count > n)
      return;
    if (count % 5 == 0)
    {
      printBuzz();
      count++;
      init();
    }
    std::lock_guard<std::mutex> guard(mtFizz);
    lock_B.unlock();
  }
  void Itself(std::function<void()> printItself)
  {
    if (count > n)
      return;
    std::lock_guard<std::mutex> guard(mtBuzz);
    printItself();
    init();
  }
};