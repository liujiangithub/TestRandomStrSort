#pragma once
#include <list>
#include <chrono>
#include <thread>
#include <mutex>

template<class T>
class SafeQueue{
private:
	std::list<T> nodes;
	int maxCount;
	std::mutex lock;
	
public:
	SafeQueue(int maxBlockCount = 1024)
	{
		maxCount = maxBlockCount;
	}
	void Put(T &v){

	    while(1){
	    	lock.lock();
			if(nodes.size() <= maxCount){
				break;
			}else{
				lock.unlock();
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}

        }
		nodes.push_back(v);	
		lock.unlock();
	}
	int Get(T &v){
		std::lock_guard<std::mutex> locker(lock);

		if(nodes.size() > 0){
			v = nodes.front();
			nodes.pop_front();

			return 0;
		}
		return -1;
	}
    
    long Size(){
        std::lock_guard<std::mutex> locker(lock);
		
		return nodes.size();
    }
};
