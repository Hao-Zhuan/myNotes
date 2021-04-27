√1.冒泡排序100个数  //很久没手撕代码了，不过应该没太大问题
   2.读取bin文件中float数据//刚搜到bin的存储方式就是二进制存储。。。
			//本题应该是考察float类型二进制文件的补码转换
√3.bash txt中计数“Xilinx”数目
	cat Xilinx.txt |grep -o "Xilinx" |wc -l
	其中-o表示统计数目、wc -l为行数
	本题没想起来，但还是应该写上man grep
   4.1~n 
	mod3==0输出fizz
	mod5==0输出buzz
	mod3==mod5==0输出fizzbuzz
     信号量

 √5.并发并行区别、多进程多线程区别
 √6.计数文件夹下文件数、将其权限设为最低级
	统计个数：find -type f |wc -l	//f代表普通格式的文件
	权限更改：sudo chmod 777 -R .  //-R表示目录
	题目好像是要求同时满足？暂不清楚
	
 √7.git 相关操作：题目不太记得了，不过可以参考本Repository中的git