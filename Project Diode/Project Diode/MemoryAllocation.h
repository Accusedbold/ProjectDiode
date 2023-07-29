/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    MemoryAllocation.h
  \author  John Salguero
  \date    June 18, 2023
  \brief
    This header file declares the global new and delete functions, 
    which manages all the memory used in the game
*/
/********************************************************************/
#ifndef _MemoryAllocation
	#define _MemoryAllocation

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new(size_t size);
_NODISCARD _Ret_maybenull_ _Success_(return != NULL) _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new(size_t size, const std::nothrow_t&) noexcept(true);
_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new[](size_t size);
_NODISCARD _Ret_maybenull_ _Success_(return != NULL) _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new[](size_t size, const std::nothrow_t&) noexcept(true);

void operator delete(void* ptr) noexcept(true);
void operator delete(void* ptr, const std::nothrow_t&) noexcept(true);
void operator delete[](void* ptr) noexcept(true);
void operator delete[](void* ptr, const std::nothrow_t&)  noexcept(true);

#endif // !_MemoryAllocation
