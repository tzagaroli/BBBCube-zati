#ifndef FWMEMORY_H
#define FWMEMORY_H
#include <cstdlib>

constexpr size_t cMakeAlignmentSize(size_t size)
{
	return ((size + sizeof(int) - 1) / sizeof(int)) * sizeof(int);
}

#endif
