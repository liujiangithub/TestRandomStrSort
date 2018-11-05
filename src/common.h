#pragma once
#include <array>
#include <sys/sysinfo.h>

typedef std::array<char, 12> RandomStrType;

static void PrintStr(RandomStrType &str)
{
	for(size_t i = 0; i < str.size(); i++){
		printf("%c", str[i]);
	}
	printf("\n");
}
static void BindCpu(int i)
{
	int cpu_num = get_nprocs();
	if(i >= cpu_num || i < 0)
	{ 
		throw std::runtime_error("bind cpu thread failed");
	} 

	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(i,&mask);

	if(-1 == pthread_setaffinity_np(pthread_self() ,sizeof(mask),&mask)) {
		throw std::runtime_error("bind cpu thread failed");
	} 
}
