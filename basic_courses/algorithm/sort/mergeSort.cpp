//sort--mergeSort
//时间复杂度O(NlogN) 
//最好最坏复杂度均为O(NlogN)
//稳定排序
#include <iostream>
#include <vector>

void merge(std::vector<int> &arr, int p, int q, int r)
{
  int n1 = q - p, n2 = r - q;
  int *L = new int[n1], *R = new int[n2];
  for (int i = 0; i < n1; ++i)
    L[i] = arr[p + i];
  for (int i = 0; i < n2; ++i)
    R[i] = arr[q + i];
  int i = 0, j = 0;
  int k = p;
  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j])
      arr[k++] = L[i++];
    else
      arr[k++] = R[j++];
  }
  while (i < n1)
    arr[k++] = L[i++];
  while (j < n2)
    arr[k++] = R[j++];
  delete[] L;
  delete[] R;
}
void merge_sort(std::vector<int> &arr, int p, int r)
{
  if (p < r - 1)
  {
    int q = p + (r - p) / 2;
    merge_sort(arr, p, q);
    merge_sort(arr, q, r);
    merge(arr, p, q, r);
  }
}

int main()
{
  std::vector<int> arr = {1, 3, 4, 5, 6, 7, 2, 8, 0, 9};
  merge_sort(arr,0,arr.size());
  for(auto i:arr)std::cout<<i<<" ";
  return 0;
}
