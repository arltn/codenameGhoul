// StackAllocationTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>

class toBeAllocated
{
public:
	int holdData;
	toBeAllocated(){};
	void init(int data)
	{ 
		holdData = data; 
	};
};

class StackAllocator
{
public:
	typedef unsigned __int32 U32, Marker;

	explicit StackAllocator(U32 stackSize_bytes);

	void* alloc(U32 size_bytes);

	inline Marker getMarker()
	{
		return stackTop;
	};
	void freeToMarker(Marker marker);

	inline void clear()
	{
		stackTop = absoluteStackTop;
	};
private:
	Marker stackTop;
	Marker absoluteStackTop;
protected:
};

StackAllocator::StackAllocator(U32 stackSize_bytes)
{
	absoluteStackTop = (U32) malloc(stackSize_bytes);
	stackTop = absoluteStackTop;
};

void* StackAllocator::alloc(U32 size_bytes)
{
	uintptr_t pRet = stackTop + size_bytes;
	stackTop += size_bytes;
	return reinterpret_cast<void*>(pRet);
};

void StackAllocator::freeToMarker(Marker marker)
{
	U32 difference = stackTop - marker;
	stackTop -= difference;
};

int _tmain(int argc, _TCHAR* argv[])
{
	StackAllocator memAlloc(256);
	toBeAllocated* x = (toBeAllocated*)memAlloc.alloc(sizeof(toBeAllocated));
	x->init(10);
	unsigned __int32 holdMarker = memAlloc.getMarker();
	toBeAllocated* y = (toBeAllocated*)memAlloc.alloc(sizeof(toBeAllocated));
	y->init(11);
	std::cout << "SizeOf toBeAllocated: " << sizeof(toBeAllocated) << std::endl;
	std::cout << "X value: " << x->holdData << std::endl;
	std::cout << "X Address: " << x << std::endl;
	memAlloc.freeToMarker(holdMarker);
	std::cout << "Y value: " << y->holdData << std::endl;
	std::cout << "Y Address: " << y << std::endl;
	y = (toBeAllocated*)memAlloc.alloc(sizeof(toBeAllocated));
	y->init(12);
	std::cout << "Y value: " << y->holdData << std::endl;
	std::cout << "Y Address: " << y << std::endl;
	memAlloc.clear();
	x = (toBeAllocated*)memAlloc.alloc(sizeof(toBeAllocated));
	x->init(13);
	y = (toBeAllocated*)memAlloc.alloc(sizeof(toBeAllocated));
	y->init(14);
	std::cout << "X value: " << x->holdData << std::endl;
	std::cout << "X Address: " << x << std::endl;
	std::cout << "Y value: " << y->holdData << std::endl;
	std::cout << "Y Address: " << y << std::endl;


	
	system("PAUSE");
	return 0;
}

