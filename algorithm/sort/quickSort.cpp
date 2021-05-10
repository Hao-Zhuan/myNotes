//sort--quickSort
//平均时间复杂度O(NlogN) 最差O(N^2)
//不稳定
//性能好：大量顺序存储数据，在处理大规模数据中操作指针更快
//STL::sort采用的主要函数为快排，再递归超过阈值后改为堆排+插排
#include <iostream>
#include <vector>

void quickSort(std::vector<int> &arr, int l, int r)
{
  if(l>r)return;
  int i=l;
  int j=r;
  int base=arr[l];
  while(i!=j){
    while(arr[j]>=base&&j>i)j--;
    while(arr[i]<=base&&i<j)i++;
    if(i<j){
      int temp=arr[i];
      arr[i]=arr[j];
      arr[j]=temp;
    }
  }
  arr[l]=arr[i];
  arr[i]=base;
  quickSort(arr,l,i-1);
  quickSort(arr,i+1,r);
}

int main()
{
  std::vector<int> arr = {1, 3, 4, 5, 6, 7, 2, 8, 0, 9};
  quickSort(arr,0,arr.size()-1);
  for(auto i:arr)std::cout<<i<<" ";
  return 0;
}
