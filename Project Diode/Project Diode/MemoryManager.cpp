/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    MemoryManager.h
  \author  John Salguero
  \date    June 18, 2023
  \brief
    This cpp file defines the MemoryManager class, which is a class that
    manages all the memory used in the game
*/
/********************************************************************/
#include "stdafx.h"         // size_t, malloc, free, memcpy_s
#include "MemorySlotMap.h"  // MemorySlotMap

MemoryManager* MemoryManager::m_Instance = new(malloc(sizeof(MemoryManager))) MemoryManager;

/******************************************************************************/
/*!
          MemoryManager

\author   John Salguero

\brief    Constructs the memory manager. Allocates the heap used for the game
          as well as components of the memory manager used to manage the
          heap.

\param    bytes
          The size of the allocation

*/
/******************************************************************************/
MemoryManager::MemoryManager(size_t bytes) : m_HeapSize(bytes)
{
  m_HeapData = malloc(m_HeapSize);
  m_AllocatedEnd = reinterpret_cast<type_ptr>(m_HeapData);
}

/******************************************************************************/
/*!
          GetInstance

\author   John Salguero

\brief    Returns an instance to the memory manager.

\return   MemoryManager*
          The pointer to the singleton MemoryManager

*/
/******************************************************************************/
MemoryManager* MemoryManager::GetInstance()
{
  return m_Instance;
}

/******************************************************************************/
/*!
          DestroyInstance

\author   John Salguero

\brief    Frees up the resources of the memory Manager

\return   void

*/
/******************************************************************************/
void MemoryManager::DestroyInstance()
{
  m_Instance->~MemoryManager();
}

/******************************************************************************/
/*!
          ~MemoryManager

\author   John Salguero

\brief    Destructor for the Memory Manager. Deallocates the heap used for the
          game as well as all the components used for managing the memory

*/
/******************************************************************************/
MemoryManager::~MemoryManager()
{
  free(const_cast<void*>(m_HeapData));
}


/******************************************************************************/
/*!
          Allocate

\author   John Salguero

\brief    Given an size to allocate, looks at the heap for the next available
          block usable and uses that to allocate the space.

\param    bytes
          The size of the new allocation

\return   The pointer to the allocated space

*/
/******************************************************************************/
void* MemoryManager::Allocate(size_t bytes)
{
  auto mapIt = m_MemoryMaps.find(bytes);
  if (mapIt != m_MemoryMaps.end())
    return mapIt->second.Allocate();
  return m_MemoryMaps.emplace(bytes, MemorySlotMap(bytes)).first->second.Allocate();
}

/******************************************************************************/
/*!
          Deallocate

\author   John Salguero

\brief    Given an address to deallocate, looks at the block infos to determine
          the location, and consolidates the information on the block list.

\param    address
          The size of the new allocation

\return   Whether it deallocated the address successfully

*/
/******************************************************************************/
bool MemoryManager::Deallocate(void* address)
{
  for (auto &map : m_MemoryMaps)
  {
    if (map.second.Contains(address))
    {
      map.second.Deallocate(address);
      return true;
    }
  }
  return false;
}

void MemoryManager::GetNextBlock(size_t size, type_ptr& begin, type_ptr& end)
{
  m_MemoryLock.lock();
  {
    size_t amount;
    begin = m_AllocatedEnd + 1;
    if (size < 100)
      amount = 1000;
    else if (size < 1000)
      amount = 100;
    else if (size < 10000)
      amount = 10;
    else
      amount = 1;
    m_AllocatedEnd = begin + (size + sizeof(MemoryManager::BlockInfo)) * amount;
    end = m_AllocatedEnd;
    if (m_AllocatedEnd - reinterpret_cast<type_ptr>(m_HeapData) > m_HeapSize)
      throw std::exception("Out of Memory");
  }
  m_MemoryLock.unlock();
}
