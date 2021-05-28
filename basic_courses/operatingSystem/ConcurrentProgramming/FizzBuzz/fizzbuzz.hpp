//信号量的做法
#pragma once
#include <iostream>
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