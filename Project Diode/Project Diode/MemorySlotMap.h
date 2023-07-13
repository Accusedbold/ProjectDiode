/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    MemorySlotMap.h
  \author  John Salguero
  \date    July 13, 2023
  \brief
    This header file declares the MemorySlotMap class, which is a
    modified version of the slot Map as described by Allan Deutsch's
    talk at C++Now 2017

    This has been inspired by Allan Deutsch's talk at C++Now 2017
    Link:
    https://www.youtube.com/watch?v=SHaAR7XPtNU&ab_channel=CppNow
*/
/********************************************************************/
#ifndef MemorySlotMap_H
#define MemorySlotMap_H

template <size_t size>
class MemorySlotMap {

  struct FreeBlock {
    FreeBlock* m_Next;
  };

public:
  MemorySlotMap<size>(unsigned long long begin, unsigned long long end) :
    m_BeginBoundary(begin), m_EndBoundary(end)
  {
    m_FreeList = reinterpret_cast<FreeBlock*>(begin);
    m_FreeListTail = m_FreeList;
    for (int i = begin; i < (end - (sizeof(FreeBlock) + size) + 1); i += sizeof(FreeBlock) + size)
    {
      m_FreeListTail->m_Next = reinterpret_cast<FreeBlock*>(i);
    }
  }
  // Allocates memory
  void* Allocate();
  // Deallocates memory
  void Deallocate(void*);

private:
  // Free list of blocks
  FreeBlock* m_FreeList;
  // Tail of the free list
  FreeBlock* m_FreeListTail;
  // Set of Allocated memory
  std::set<void*, std::less<Key>, Allocator<void*>> m_Allocated;
  // Gets more memory from the memory Manager
  void Grow();

  unsigned long long m_BeginBoundary;
  unsigned long long m_EndBoundary;

};

#endif
