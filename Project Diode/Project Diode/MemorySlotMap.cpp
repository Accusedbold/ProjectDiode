/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    MemorySlotMap.cpp
  \author  John Salguero
  \date    July 13, 2023
  \brief
    This cpp file defines the MemorySlotMap class functions, which is a
    modified version of the slot Map as described by Allan Deutsch's
    talk at C++Now 2017

    This has been inspired by Allan Deutsch's talk at C++Now 2017
    Link:
    https://www.youtube.com/watch?v=SHaAR7XPtNU&ab_channel=CppNow
*/
/********************************************************************/
#include "stdafx.h"
#include "MemoryManager.h"
#include "MemorySlotMap.h"

MemorySlotMap::MemorySlotMap(size_t const& size) :
  m_BeginBoundary(0), m_EndBoundary(0), m_MemoryManagerInstance(MemoryManager::GetInstance()),
  m_FreeList(nullptr), m_FreeListTail(nullptr), m_Size(size)
{
  Grow();
}

MemorySlotMap::MemorySlotMap(MemorySlotMap&& rValue)
{
  m_BeginBoundary = rValue.m_BeginBoundary;
  m_EndBoundary = rValue.m_EndBoundary;
  m_MemoryManagerInstance = rValue.m_MemoryManagerInstance;
  m_FreeList = rValue.m_FreeList;
  m_FreeListTail = rValue.m_FreeListTail;
  m_Size = rValue.m_Size;
  m_Allocated.swap(rValue.m_Allocated);
}

void* MemorySlotMap::Allocate()
{
  void* retVal = nullptr;
  if (m_FreeList == m_FreeListTail)
    Grow();
  m_Mutex.lock();
  {
    retVal = reinterpret_cast<char*>(m_FreeList) + sizeof(m_FreeList);
    m_FreeList = m_FreeList->m_Next;
    m_Allocated.emplace(retVal);
  }
  m_Mutex.unlock();
  return retVal;
}

void MemorySlotMap::Deallocate(void* address)
{
  if (m_Allocated.contains(address))
  {
    m_Mutex.lock();
    m_Allocated.erase(address);
    m_FreeListTail->m_Next = reinterpret_cast<FreeBlock*>(address) - 1;
    m_FreeListTail = m_FreeListTail->m_Next;
    m_FreeListTail->m_Next = nullptr;
    m_Mutex.unlock();
  }
}

bool MemorySlotMap::Contains(void* address) const
{
  if (m_BeginBoundary > reinterpret_cast<type_ptr>(address))
    return false;
  return m_Allocated.contains(address);
}

inline void MemorySlotMap::Grow()
{
  m_Mutex.lock();

  type_ptr begin;
  m_MemoryManagerInstance->GetNextBlock(m_Size, begin, m_EndBoundary);
  if (!m_BeginBoundary)
    m_BeginBoundary = begin;

  for (type_ptr i = begin; i <= m_EndBoundary - (sizeof(FreeBlock) + m_Size); i += sizeof(FreeBlock) + m_Size)
  {
    if (!m_FreeListTail)
    {
      m_FreeListTail = reinterpret_cast<FreeBlock*>(i);
      m_FreeList = m_FreeListTail;
    }
    else
    {
      m_FreeListTail->m_Next = reinterpret_cast<FreeBlock*>(i);
      m_FreeListTail = m_FreeListTail->m_Next;
    }
  }
  m_FreeListTail->m_Next = nullptr;
  m_Mutex.unlock();
}