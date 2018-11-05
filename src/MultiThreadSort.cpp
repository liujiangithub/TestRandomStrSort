#include "common.h"
#include <algorithm>
#include <thread>
#include "SafeThreadQueue.h"
#include "RandomStrGenerator.h"
#include <chrono>
#include <signal.h>
#include <exception>




static bool stopFlag = false;
#define PRODUCT_GROUP_COUNT 1024*16

//捕捉ctrl+c信号，以便线程退出和join
static void HandleSignal(int sig){
    if(sig == SIGINT || sig == SIGQUIT){
        printf("\nrecv signal %d, quit process...\n", sig);
        stopFlag = true;
    }
}


void GenerateThreadRun(RandomStrGenerator *generator, SafeQueue<std::vector<RandomStrType> *> *queue)
{
#ifdef BIND_CPU
	BindCpu(0);
#endif
	while(!stopFlag){
	    //将多个随即字符串打包后再一起塞入队列，增加队列吞吐率
        std::vector<RandomStrType> *product = new std::vector<RandomStrType>(PRODUCT_GROUP_COUNT);
        for(size_t i = 0; i < product->size(); i++){
		    generator->GetRandomStr((*product)[i]);
        }
		queue->Put(product);	
    }
}

int main()
{
	try{
		signal(SIGINT, HandleSignal);
		signal(SIGQUIT, HandleSignal);
		srand(time(NULL));
		SafeQueue<std::vector<RandomStrType> * > queue;
		RandomStrGenerator generator;
		std::thread generatorThread(GenerateThreadRun, &generator, &queue);
	    std::chrono::steady_clock::time_point t1, t2;


	#ifdef BIND_CPU
		BindCpu(0);
	#endif
		t1 = std::chrono::steady_clock::now();
		long count = 0;
		while(!stopFlag || queue.Size() > 0){
	        std::vector<RandomStrType> *product;
			if(0 == queue.Get(product)){
				//get data success
				//printf("before sort:");
				//PrintStr(str);
				for(size_t i = 0; i < product->size(); i++){
	                RandomStrType &str = (*product)[i];
				    std::sort(str.begin(), str.end());
				    count++;
	            }
			    t2 = std::chrono::steady_clock::now();
	            double duration = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count();
			    if(duration >= 5.f){
			        printf("average count %f\n", (double)count/duration);
			        count = 0;
			        t1 = std::chrono::steady_clock::now();
	            }
	            delete product;
				//printf("after sort:");
				//PrintStr(str);
			}
		}

		generatorThread.join();
	}catch(std::exception &e){
		fprintf(stderr, "catch exception %s\n", e.what());
	}

	return 0;
}
