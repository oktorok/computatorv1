#include "computator.h"
#include <vector>

template <typename T>
vector<T> sub_vector(vector<T> src, int start, int end)
{
	vector<T> sub(src.begin() + start, src.begin() + end);
	return sub;
}

