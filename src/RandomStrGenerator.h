#pragma once
#include "common.h"
#include <stdlib.h>
#include <vector>

class RandomStrGenerator{
private:
	std::vector<char> mRandomScope;
public:
	RandomStrGenerator();
	void GetRandomStr(RandomStrType &out);
};

