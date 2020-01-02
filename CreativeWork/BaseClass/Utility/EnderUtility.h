#pragma once

//delete Utility
template <class T>
inline void Delete(T*& p)
{
	if (p)
	{
		delete p;
	}
	p = nullptr;
}

template <class T>
inline void Release(T*& p)
{
	if (p)
	{
		p->Release();
	}
	p = nullptr;
}

template <class T>
inline void DeleteArray(T*& p)
{
	if (p)
	{
		delete[] p;
	}
	p = nullptr;
}

#include <list>
#include <vector>

template <class T>
void DeleteListElem(std::list<T*>& arr, T* elem)
{
	typename std::list<T*>::iterator itr;
	for (itr = arr.begin(); itr != arr.end();)
	{
		if ((*itr) == elem)
		{
			it = arr.erase(it);
		}
		else
		{
			++itr;
		}
	}
}

template <class T>
void DeleteList(std::list<T*>& arr)
{
	typename std::list<T*>::iterator itr;
	for (itr = arr.begin(); itr != arr.end(); itr++)
	{
		Delete(*itr);
	}
	arr.clear();
}

template <class T>
void ReleaseVector(std::vector<T*>& arr)
{
	for (auto itr = arr.begin(); itr != arr.end(); itr++)
	{
		Release(*itr);
	}
	arr.clear();
}