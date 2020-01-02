#pragma once

#include <memory>

template <class T>
class CSingleton
{
protected:

	CSingleton() {};

private:

	typedef std::unique_ptr<T> singleton_pointer_type;

	CSingleton(const CSingleton&) = delete;
	CSingleton& operator=(const CSingleton&) = delete;
	CSingleton(CSingleton&&) = delete;
	CSingleton& operator=(CSingleton&&) = delete;

	inline static T* createInstance() {
		return new T();
	}
	inline static T& getReference(const singleton_pointer_type &ptr){
		return *ptr;
	}

public:


	virtual ~CSingleton() {};

	static T& GetInstance() 
	{
		static typename T::singleton_pointer_type s_singleton(T::createInstance());
		return getReference(s_singleton);
	}

};