# RandomStrSort

测试多线程和单线程随机字符串生成和排序效率的程序，每隔五秒输出平均每秒处理了多少个随机字符串
注：由于上周末没有时间的关系，没有用cmake，使用简单的Makefile，部分流程也没有去做抽象。
部分源码说明：
	common.h一些公共的函数
	SafeThreadQueue.h 模板线程安全FIFO
	RandomStrGenerator.cpp 生成12bytes字母和数字字符串
	SingleThreadSort.cpp 单线程执行随机和排序
	MultiThreadSort.cpp 多线程执行随即和排序

程序说明：
	MultiThreadSort 多线程执行生成和排序
	SingleThreadSort 单线程执行生成和排序
	MultiThreadSortSingleCpu 程序执行逻辑与MultiThreadSort相同，只是强行绑定了一个CPU核
	MultiThreadSortSingleCpu 程序执行逻辑与MultiThreadSort相同，只是在多核CPU上模拟单核CPU的执行

build:
	cd RandomStrSort
	make


测试系统:ubuntu16.04 
测试cpu: Intel(R) Xeon(R) CPU E3-1231 v3 @ 3.40GHz
测试结果（可见test_result.png）：
liujian@liujian-B85-HD3-A:~/devel/test_cpp/RandomStrSort$ ./MultiThreadSort
average count 4653884.398864
average count 4751940.725604
average count 4651123.509344
average count 4733543.606984
average count 4562420.224344
^C
recv signal 2, quit process...
liujian@liujian-B85-HD3-A:~/devel/test_cpp/RandomStrSort$ ./SingleThreadSort
average count 3460005.029768
average count 3430066.148549
average count 3580267.770642
average count 3426608.089663
average count 3396661.582337
^C
liujian@liujian-B85-HD3-A:~/devel/test_cpp/RandomStrSort$ ./MultiThreadSortSingleCpu 
average count 2341561.919556
average count 2366205.492677
average count 2364837.060378
average count 2325670.513188
average count 2331645.211902
^C
recv signal 2, quit process...
liujian@liujian-B85-HD3-A:~/devel/test_cpp/RandomStrSort$ ./SingleThreadSortSingleCpu 
average count 3404547.287650
average count 3447517.020729
average count 3461699.082995
average count 3427477.391089
average count 3382086.388501
average count 3498385.328633
average count 3400335.864994
average count 3376101.510196
average count 3414791.645651



总结：
	由于没有单核CPU测试环境，多线程版本采用绑定CPU的方式绑定在一个核上面执行
	在多核CPU上，多线程版本强于单线程版本，因为两个线程在两个CPU核线程并发执行，可以有效减少执行时间
	在单核CPU上，单线程版本强于多线程版本，因为只有一个核，线程的调度导致该核时间片的切换，以及多余的队列进出动作导致了该结果







