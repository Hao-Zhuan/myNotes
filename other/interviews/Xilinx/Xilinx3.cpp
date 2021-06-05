//题目要求：从bin文件中读取浮点数
#include <iostream>
int main()
{
  FILE *fp;

  float f1 = 123.456;
  float f2 = 0.00;

  if ((fp = fopen(".\\xilinx3_test.bin", "w+b")) == NULL)
  {
    std::cout<<"open fail\n";
    return 0;
  }
//先写一个值
  fwrite(&f1, sizeof(float), 1, fp);
//写完后将光标移动回起始点
  fseek(fp, 0, SEEK_SET);
//读入数据
  fread(&f2, sizeof(float), 1, fp);
  std::cout<<"f2 = "<<f2;
  fclose(fp);
  return 0;
}
