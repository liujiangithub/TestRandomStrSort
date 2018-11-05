#include "RandomStrGenerator.h"

RandomStrGenerator::RandomStrGenerator()
{
	for(int i = '0'; i <= '9'; i++){
		mRandomScope.push_back(i);
	}
	for(int i = 'A'; i <= 'Z'; i++){
		mRandomScope.push_back(i);
	}
	for(int i = 'a'; i <= 'z'; i++){
		mRandomScope.push_back(i);
	}
}


void RandomStrGenerator::GetRandomStr(RandomStrType &out)
{
	for(int i = 0; i < out.size(); i++){
		out[i] = mRandomScope[rand() % mRandomScope.size()];
	}
}
