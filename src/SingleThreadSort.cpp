#include "RandomStrGenerator.h"
#include <algorithm>
#include <chrono>
#include <list>
#include <exception>

int main()
{
	try{
		#ifdef BIND_CPU
		BindCpu(0);
		#endif
		srand(time(NULL));
		RandomStrGenerator generator;
		long count = 0;
		auto t1 = std::chrono::steady_clock::now();
		auto t2 = t1;
		while(1){
			RandomStrType str;
			generator.GetRandomStr(str);
			//printf("before sort:");
			//PrintStr(str);
			std::sort(str.begin(), str.end());
			count ++;

			t2 =  std::chrono::steady_clock::now();
			double duration = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count();
				if(duration >= 5.f){
				printf("average count %f\n", (double)count/duration);
				count = 0;
				t1 = std::chrono::steady_clock::now();
			}
		}
			//printf("after sort:");
			//PrintStr(str);
	}catch(std::exception &e){
		fprintf(stderr, "catch exception %s\n", e.what());
	}
    return 0;
}

