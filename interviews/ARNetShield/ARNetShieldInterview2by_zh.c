/* 2.把一个文本文件中的内容做如下转换后（假定文件大小不大于10M字节），生成另一个新的文件
 把文件中的所有*号提前，放在文件的最前面，其它内容不变，保存为一个新文件
 比如：hello *wor*ld*  处理后新文件的内容为:***hello world
 */

//使用说明 同目录下新建两个文本文档，一个用于输入，一个用于存储输出
//将程序中第14、15行的输入输出文件名更改为刚刚新建的文件名


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _MAX_LINE  1024 //文件每行大小
#define _InputFileName "myInput.txt"   //用于输入的文件名
#define _OutputFileName "myOutput.txt" //用于输出的文件名

unsigned long long myCount()
{
  static unsigned long long count = 0; //用于计数'*'的个数
  char buf[_MAX_LINE];
  FILE *fI;
  int len;
  if ((fI = fopen(_InputFileName, "r")) == NULL)
  {
    perror("fail to read");
    exit(1);
  }
  while (fgets(buf, _MAX_LINE, fI) != NULL)
  {
    len = strlen(buf);
    for (int temp = 0; temp < len; temp++)
    {
      if (buf[temp] == '*')
        count++;
    }
    //printf("%s ", buf);  //本行用于测试
  }
  return count;
}

void myWrite(unsigned long long count)
{
  char buf[_MAX_LINE]; /*缓冲区*/
  FILE *fI;            /*文件指针*/
  int len;             /*行字符个数*/
  fI = fopen(_InputFileName, "r");

  FILE *fO = NULL;
  fO = fopen(_OutputFileName, "w+");

  while (count--)       //输出'*'
    fprintf(fO, "*");

  while (fgets(buf, _MAX_LINE, fI) != NULL)
  {
    len = strlen(buf);
    char wbuf[len];
    for (int temp = 0, i = 0; temp < len; temp++)
    {
      if (buf[temp] != '*')
        wbuf[i++] = buf[temp];
    }
    fprintf(fO, "%s", wbuf);//输出非'*'
  }
  fclose(fO);
  printf("finished!\n");
}

int main()
{
  myWrite(myCount());
  return 0;
}