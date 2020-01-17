#pragma once

#include <vector>
#include <iostream>

template <typename T>
T& GetTemplate(std::vector<T> vec, int index)
{
	if (index >= vec.size())
	{
		std::cout << "Buffer Size Over in Getter." << std::endl;
		return vec[0];
	}
	else
	{
		return vec[index];
	}
}