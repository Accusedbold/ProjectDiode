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


class MemorySlotMap {

  using FreeBlock = MemoryManager::BlockInfo;

public:
  MemorySlotMap(size_t const&csize);
  MemorySlotMap(MemorySlotMap && rValue);
  // Allocates memory
  void* Allocate();
  // Deallocates memory
  void Deallocate(void*);
  // Contains Address
  bool Contains(void* address) const;

private:
  // Gets more memory from the memory Manager
  void Grow();
  // Free list of blocks
  FreeBlock* m_FreeList;
  // Tail of the free list
  FreeBlock* m_FreeListTail;
  // Set of Allocated memory
  std::set<void*, std::less<void*>, Allocator<void*>> m_Allocated;
  // Instance of the memory Manager
  MemoryManager* m_MemoryManagerInstance;

  // The begining boundry of available memory
  type_ptr m_BeginBoundary;
  // The end boundry of available memory
  type_ptr m_EndBoundary;
  // Mutex for multithreaded access
  std::mutex m_Mutex;
  // Size of each block this map manages
  size_t m_Size;

}; 
#endif
