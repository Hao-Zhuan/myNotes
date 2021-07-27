/* 写一个函数处理文件路径：
输入任何一个路径字符串，把它转换成不含.和..的绝对文件路径，对不合法的路径/错误的路径给出提示
 比如：c:\1\2\..\3\.\1.txt  输出c:\1\3\1.txt
 比如：c:\1\3\1.txt  输出c:\1\3\1.txt
 *//*  */

//只对题目中要求的非法路径输出进行了处理 其他情况目前想到的使用c++regex正则表达式库来处理，或者直接新建一个目录，捕获异常
#include <stdio.h>
#include <string.h>
#define _MAXLength 1000 //文件路径最大长度

char *absPath(char *path)
{
  char *res;
  char *temp = res;
  int count = 0;
  while (*path)
  {
    if (*path != '.')
    {
      temp[count++] = *path;
      path++;
    }
    else
    {
      if (*(path + 1) && *(path + 1) == '\\'){
        path += 2;
        printf("输入非法！\n");
      }
        
      else if ((*(path + 1) && *(path + 2)) && (*(path + 1) == '.') && (*(path + 2) == '\\')){
        path += 3;
        printf("输入非法！\n");
      }
        
      else
      {
        temp[count++] = *path;
        path++;
      }
    }
  }
  return res;
}

void testFunc()
{
  printf("请输入字符串：\n");
  char path[_MAXLength] = {0};
  scanf("%s", &path[0]);
  char *p = absPath(path);
  printf("%s\n", p);
}

int main(void)
{
  while (1)
  {
    testFunc();
  }
  return 0;
}