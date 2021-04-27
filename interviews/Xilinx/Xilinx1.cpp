//bubbleSort
#include <iostream>
#include <vector>
#define number (100) //设定数目
//输入程序
std::vector<int> myInput()
{
  size_t n = number;
  std::vector<int> arr(number, 0);
  while (n--)
    std::cin >> arr[number - n];
  return arr;
}
//排序
void bubbleSort(std::vector<int> &arr)
{
  for (int i = 0; i < number - 1; i++)
  {
    bool flag = true;
    for (int j = 0; j < number - 1 - i; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        flag = false;
      }
    }
    if (flag)
      return;
  }
  return;
}

int main()
{
  std::vector<int> arr(100, 0);
  arr = myInput();
  bubbleSort(arr);
  for (auto i : arr)
    std::cout << i << " ";
  return 0;
}