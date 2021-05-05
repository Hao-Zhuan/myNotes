//本文档列出了对于按序要求访问的其余做法
#include <iostream>
#include <unistd.h>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <semaphore.h>
#include <future>
#include <chrono>
class myFizzBuzz
{
public:
  int n;
  int count;
  myFizzBuzz(int n) : n(n) {}
  myFizzBuzz() = default;
  ~myFizzBuzz() = default;
  std::function<void()> printFizz = []() { std::cout << "fizz "; };
  std::function<void()> printBuzz = []() { std::cout << "buzz "; };
  std::function<void()> printFizzBuzz = []() { std::cout << "fizzbuzz "; };
  std::function<void(int)> printItself = [](int val) { std::cout << val << " "; };
};

class So1 : public myFizzBuzz //面试时写的思路,本方法能用，但不同线程调用了不属于自己的锁，故本行为很危险
{
private:
  std::mutex mtFizz, mtBuzz, mtFizzBuzz;

public:
  So1()
  {
    mtFizz.lock();
    mtBuzz.lock();
    mtFizzBuzz.lock();
  }
  void FizzBuzz(std::function<void()> printFizzBuzz)
  {
    printFizzBuzz();
    mtFizzBuzz.unlock();
  }
  void Fizz(std::function<void()> printFizz)
  {
    mtFizzBuzz.lock();
    printFizz();
    mtFizzBuzz.unlock();
    mtFizz.unlock();
  }
  void Buzz(std::function<void()> printBuzz)
  {
    mtFizz.lock();
    printBuzz();
    mtFizz.unlock();
    mtBuzz.unlock();
  }
  void Itself(std::function<void()> printItself)
  {
    mtBuzz.lock();
    printItself();
    mtBuzz.unlock();
  }
};

class So2 : public myFizzBuzz //So1+RAII机制
{
  std::mutex mtFizzBuzz, mtFizz, mtBuzz;
  std::unique_lock<std::mutex> lock_FB, lock_F, lock_B;

public:
  So2() : lock_FB(mtFizzBuzz, std::try_to_lock), lock_F(mtFizz, std::try_to_lock), lock_B(mtBuzz, std::try_to_lock) {}
  void FizzBuzz(std::function<void()> printFizzBuzz)
  {
    printFizzBuzz();
    mtFizzBuzz.unlock();
  }
  void Fizz(std::function<void()> printFizz)
  {
    std::lock_guard<std::mutex> guard(mtFizzBuzz);
    printFizz();
    lock_F.unlock();
  }
  void Buzz(std::function<void()> printBuzz)
  {
    std::lock_guard<std::mutex> guard(mtFizz);
    printBuzz();
    lock_B.unlock();
  }
  void Itself(std::function<void()> printItself)
  {
    std::lock_guard<std::mutex> guard(mtBuzz);
    printItself();
  }
};

class So3 : public myFizzBuzz //条件变量
{
  std::condition_variable cv;
  std::mutex mt;
  int count = 0;

public:
  void FizzBuzz(std::function<void()> printFizzBuzz)
  {
    printFizzBuzz();
    count = 1;
    cv.notify_all();
  }

  void Fizz(std::function<void()> printFizz)
  {
    std::unique_lock<std::mutex> lock(mt);
    cv.wait(lock, [this]() { return count == 1; });
    printFizz();
    count = 2;
    cv.notify_all();
  }
  void Buzz(std::function<void()> printBuzz)
  {
    std::unique_lock<std::mutex> lock(mt);
    cv.wait(lock, [this]() { return count == 2; });
    printBuzz();
    cv.notify_all();
  }
  void Itself(std::function<void()> printItself)
  {
    std::unique_lock<std::mutex> lock(mt);
    cv.wait(lock, [this]() { return count == 2; });
    printItself();
  }
};

class So4 : public myFizzBuzz //信号量
{
  sem_t sem_FB, sem_F, sem_B;

public:
  So4()
  {
    sem_init(&sem_FB, 0, 0), sem_init(&sem_F, 0, 0), sem_init(&sem_B, 0, 0);
  }
  void FizzBuzz(std::function<void()> FizzBuzz)
  {
    printFizzBuzz();
    sem_post(&sem_FB);
  }

  void Fizz(std::function<void()> Fizz)
  {
    sem_wait(&sem_FB);
    printFizz();
    sem_post(&sem_F);
  }
  void Buzz(std::function<void()> Buzz)
  {
    sem_wait(&sem_F);
    printBuzz();
    sem_post(&sem_B);
  }
  void Itself(std::function<void()> Itself)
  {
    sem_wait(&sem_B);
    printItself(count);
  }
};

//c++11 std::future:用来获取异步操作结果的模板类
//std::promise调用std::promise::set_value来通知future对象
class So5 : public myFizzBuzz
{
  std::promise<void> proFB, proF, proB;

public:
  void FizzBuzz(std::function<void()> printFizzBuzz)
  {
    printFizzBuzz();
    proFB.set_value();
  }

  void Fizz(std::function<void()> printFizz)
  {
    proFB.get_future().wait();
    printFizz();
    proF.set_value();
  }
  void Buzz(std::function<void()> printBuzz)
  {
    proF.get_future().wait();
    printBuzz();
    proB.set_value();
  }
  void Itself(std::function<void()> printItself)
  {
    proB.get_future().wait();
    printItself();
  }
};
//c++11 std::future:用来获取异步操作结果的模板类
//std::promise调用std::promise::set_value来通知future对象
class So6 : public myFizzBuzz
{
  std::function<void()> print = []() {};
  std::packaged_task<void()> pt_FB{print}, pt_F{print}, pt_B{print};

public:
  void FizzBuzz(std::function<void()> printFizzBuzz)
  {
    printFizzBuzz();
    pt_FB();
  }

  void Fizz(std::function<void()> printFizz)
  {
    pt_FB.get_future().wait();
    printFizz();
    pt_F();
  }
  void Buzz(std::function<void()> printBuzz)
  {
    pt_F.get_future().wait();
    printBuzz();
    pt_B();
  }
  void Itself(std::function<void()> printItself)
  {
    pt_B.get_future().wait();
    printItself();
  }
};

//原子操作：c++11中提供std::atomic<T>模板来构造原子对象
//c++标准并未规定atomic实现是否无锁，可以用is_lock_free()来查询
class So7 : public myFizzBuzz
{
  std::atomic<bool> fb{false};
  std::atomic<bool> f{false};
  std::atomic<bool> b{false};

public:
  void FizzBuzz(std::function<void()> printFizzBuzz)
  {
    printFizzBuzz();
    fb = true;
  }

  void Fizz(std::function<void()> printFizz)
  {
    while (!fb)
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    printFizz();
    f = true;
  }
  void Buzz(std::function<void()> printBuzz)
  {
    while (!f)
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    printBuzz();
    b = true;
  }
  void Itself(std::function<void()> printItself)
  {
    while (!b)
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    printItself();
  }
};
