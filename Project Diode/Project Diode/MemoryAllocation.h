#ifndef _MemoryAllocation
	#define _MemoryAllocation

void* operator new(size_t size) noexcept(false);
void* operator new(size_t size, const std::nothrow_t&) noexcept(true);
void* operator new[](size_t size) noexcept(false);
void* operator new[](size_t size, const std::nothrow_t&) noexcept(true);

void operator delete(void* ptr) noexcept(true);
void operator delete(void* ptr, const std::nothrow_t&) noexcept(true);
void operator delete[](void* ptr) noexcept(true);
void operator delete[](void* ptr, const std::nothrow_t&)  noexcept(true);

#endif // !_MemoryAllocation
