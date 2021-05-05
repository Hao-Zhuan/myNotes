/*
  题目描述：
  1~n 
	mod3==0输出fizz
	mod5==0输出buzz
	mod3==mod5==0输出fizzbuzz
 */
//信号量的做法，其余做法见4_2
#include <iostream>
#include <semaphore.h>
#include <functional>
#include <thread>
#define testNum (15)

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
//信号量的做法
class Sem : public myFizzBuzz
{
private:
  sem_t sem_f;
  sem_t sem_b;
  sem_t sem_fb;
  sem_t sem_it;

public:
  Sem(int n) : myFizzBuzz(n)
  {
    this->count = 1;
    sem_init(&sem_f, 0, 0);
    sem_init(&sem_b, 0, 0);
    sem_init(&sem_fb, 0, 0);
    sem_init(&sem_it, 0, 1);
  }
  ~Sem() = default;
  void Fizz(std::function<void()> printFizz)
  {
    while (count <= n)
    {
      sem_wait(&sem_f);
      if (count > n)
        break;
      printFizz();
      count++;
      sem_post(&sem_it);
    }
  }
  void Buzz(std::function<void()> printBuzz)
  {
    while (count <= n)
    {
      sem_wait(&sem_b);
      if (count > n)
        break;
      printBuzz();
      count++;
      sem_post(&sem_it);
    }
  }
  void FizzBuzz(std::function<void()> printFizzBuzz)
  {
    while (count <= n)
    {
      sem_wait(&sem_fb);
      if (count > n)
        break;
      printFizzBuzz();
      count++;
      sem_post(&sem_it);
    }
  }

  void Itself(std::function<void(int)> printNumber)
  {
    while (true)
    {
      sem_wait(&sem_it);
      if (count > n)
        break;
      if (count % 3 == 0 && count % 5 == 0)
      {
        sem_post(&sem_fb);
      }
      else if (count % 3 == 0)
      {
        sem_post(&sem_f);
      }
      else if (count % 5 == 0)
      {
        sem_post(&sem_b);
      }
      else
      {
        printNumber(count);
        count++;
        sem_post(&sem_it);
      }
    }
    sem_post(&sem_f);
    sem_post(&sem_b);
    sem_post(&sem_fb);
  }
};

class myTest : public Sem
{
public:
  Sem *fizzbuzz;
  std::thread th[4];
  myTest(int val) : Sem(val)
  {
    fizzbuzz = (new Sem(val));
    th[0] = std::thread(&Sem::Fizz, fizzbuzz, printFizz);
    th[1] = std::thread(&Sem::Buzz, fizzbuzz, printBuzz);
    th[2] = std::thread(&Sem::FizzBuzz, fizzbuzz, printFizzBuzz);
    th[3] = std::thread(&Sem::Itself, fizzbuzz, printItself);
  }
  ~myTest() = default;

  void runTest()
  {
    for (auto &ts : this->th)
    {
      if (ts.joinable())
        ts.join();
    }
  }
};

int main()
{
  myTest A(testNum);
  A.runTest();
  return 0;
}