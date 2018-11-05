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
测试结果（test_result.png)


总结：
	由于没有单核CPU测试环境，多线程版本采用绑定CPU的方式绑定在一个核上面执行
	在多核CPU上，多线程版本强于单线程版本，因为两个线程在两个CPU核线程并发执行，可以有效减少执行时间
	在单核CPU上，单线程版本强于多线程版本，因为只有一个核，线程的调度导致该核时间片的切换，以及多余的队列进出动作导致了该结果







