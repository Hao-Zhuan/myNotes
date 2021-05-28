//sort--shellSort
//复杂度O(N^1.5)
//不稳定
//增量选取：一般从ceil(N/2)开始，本方法展示了5个元素的情况

#include <iostream>
#include <vector>
#include <algorithm>
void shellSort(std::vector<int> &arr, int len)
{
  int h = 1, i, j;
  while (h < len / 3) //寻找合适的间隔h
  {
    h = 3 * h + 1;
  }
  while (h >= 1)
  {
    //将数组变为间隔h个元素有序
    for (i = h; i < len; i++)
    {
      //间隔h插入排序
      for (j = i; j >= h && arr[j] < arr[j - h]; j -= h)
      {
        std::swap(arr[j], arr[j - h]);
      }
    }
    h /= 3;
  }
}

int main()
{
  std::vector<int> arr = {1, 3, 2, 5, 4};
  shellSort(arr, arr.size());
  for (auto i : arr)
    std::cout << i << " ";
  return 0;
}