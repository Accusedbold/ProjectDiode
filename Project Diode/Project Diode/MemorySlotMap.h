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

  using FreeBlock = MemoryManager::BlockInfo;

public:
  MemorySlotMap<size>(unsigned long long begin, unsigned long long end) :
    m_BeginBoundary(0), m_EndBoundary(0), m_MemoryManagerInstance(MemoryManager::GetInstance()),
    m_FreeList(nullptr), m_FreeList(nullptr)
  {
    Grow();
  }
  // Allocates memory
  void* Allocate();
  // Deallocates memory
  void Deallocate(void*);

private:
  // Gets more memory from the memory Manager
  void Grow();
  // Free list of blocks
  FreeBlock* m_FreeList;
  // Tail of the free list
  FreeBlock* m_FreeListTail;
  // Set of Allocated memory
  std::set<void*, std::less<Key>, Allocator<void*>> m_Allocated;
  // Instance of the memory Manager
  MemoryManager* m_MemoryManagerInstance;

  // The begining boundry of available memory
  type_ptr m_BeginBoundary;
  // The end boundry of available memory
  type_ptr m_EndBoundary;
  // Mutex for multithreaded access
  std::mutex m_Mutex;

}; 

template<size_t size>
inline void* MemorySlotMap<size>::Allocate()
{
  void* retVal = nullptr;
  if (m_FreeList == m_FreeListTail)
    Grow();
  m_Mutex.lock();
  {
    void* retVal = reinterpret_cast<char*>(m_FreeList) + sizeof(m_FreeList);
    m_FreeList = m_FreeList->m_Next;
  }
  m_Mutex.unlock();
  return retVal;
}

template<size_t size>
inline void MemorySlotMap<size>::Deallocate(void* address)
{
  if (m_Allocated.find(address) != m_Allocated.end())
  {
    m_Mutex.lock();
    m_Allocated.erase(address);
    m_Mutex.lock();
  }
}

template<size_t size>
inline void MemorySlotMap<size>::Grow()
{
  m_Mutex.lock();
  if(!m_BeginBoundary)
    m_MemoryManagerInstance->GetNextBlock(size, m_BeginBoundary, m_EndBoundary);
  else
    m_MemoryManagerInstance->GetNextBlock(size, size_t(0), m_EndBoundary);
  
  else
  {
    m_FreeListTail->m_Next = reinterpret_cast<FreeBlock*>(m_EndBoundary - size);
    m_FreeListTail = m_FreeListTail->m_Next;
  }
  
  for (int i = m_EndBoundary - size; i >= m_BeginBoundary; i -= sizeof(FreeBlock) + size)
  {
    if (!m_FreeListTail)
    {
      m_FreeListTail = reinterpret_cast<FreeBlock*>(m_EndBoundary - size);
      m_FreeList = m_FreeListTail;
      m_FreeListTail->m_Next = nullptr;
    }
    else
      m_FreeListTail->m_Next = reinterpret_cast<FreeBlock*>(i);
  }
  m_Mutex.unlock();
}
#endif
