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
#include "stdafx.h" // size_t, malloc, free, memcpy_s

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
MemoryManager::MemoryManager(size_t bytes) : m_HeapSize(bytes), m_BlockSize(0), m_NodeData(nullptr)
{
  m_HeapData = malloc(m_HeapSize);
  m_UnusedBlocks = nullptr;
  GrowNodes();
  m_BlockList = m_UnusedBlocks;
  m_UnusedBlocks = m_UnusedBlocks->m_Next;

  m_BlockList->m_Size = m_HeapSize;
  m_BlockList->m_Address = static_cast<char*>(const_cast<void*>(m_HeapData));
  m_BlockList->m_Allocated = false;
  m_BlockList->m_Next = nullptr;
}

MemoryManager* MemoryManager::GetInstance()
{
  return m_Instance;
}

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
  for (int i = 0; i < m_BlockSize; ++i) {
    for (int j = 0; j < (i+1) * BLOCK_PAGE_SIZE; ++j) {
      m_NodeData[i][j].~BlockInfo();
    }
    free(m_NodeData[i]);
  }
  free(m_NodeData);
}

/******************************************************************************/
/*!
          GetFreeBlockInfo

\author   John Salguero

\brief    Returns an unused BlockInfo object that has been pre-allocated.

\return   The pointer to the unused BlockInfo object

*/
/******************************************************************************/
MemoryManager::BlockInfo* MemoryManager::GetFreeBlockInfo()
{
  if (!m_UnusedBlocks)
    GrowNodes();
  BlockInfo* retVal = m_UnusedBlocks;
  m_UnusedBlocks = m_UnusedBlocks->m_Next;

  return retVal;
}

/******************************************************************************/
/*!
          InsertBlock

\author   John Salguero

\brief    Given an old block describing free space, splits it into two different
          blocks if the size is larger than the new size

\param    oldBlock
          The old block to be split

\param    bytes
          The size of the new allocation

\return   The pointer to the allocated space

*/
/******************************************************************************/
void* MemoryManager::InsertBlock(BlockInfo* const oldBlock, const size_t bytes)
{
  BlockInfo* freeMem = nullptr; /* block of extra free memory from oldBlock */
  size_t oldsize = oldBlock->m_Size; /* size in bytes of the old block */
  char* address = oldBlock->m_Address; /* address of the old block */

  /* change the old block to reflect the inserted block */
  oldBlock->m_Allocated = true;
  oldBlock->m_Size = bytes;

  /* if there is memory left over, insert a new block to reflect this */
  if (bytes < oldsize)
  {
    /* get an unused node for the block info and insert it next on the list */
    freeMem = GetFreeBlockInfo();
    freeMem->m_Allocated = false;
    freeMem->m_Size = oldsize - bytes;
    freeMem->m_Address = address + bytes;
    freeMem->m_Next = oldBlock->m_Next;

    oldBlock->m_Next = freeMem;
  }

  /* return the address of the allocated memory */
  return oldBlock->m_Address;
}


/******************************************************************************/
/*!
          GrowNodes

\author   John Salguero

\brief    Allocates more nodes for the list of unused BlockInfo Objects. These
          are used to describe which parts of the heap are used and unused.

\return   void

*/
/******************************************************************************/
void MemoryManager::GrowNodes()
{
  void* newNodePointers = malloc(++m_BlockSize * sizeof(void*));
  void* newNodeData = malloc(m_BlockSize * BLOCK_PAGE_SIZE * sizeof(BlockInfo));
  if (m_NodeData) {
    std::memcpy(newNodePointers, m_NodeData, (m_BlockSize - 1) * sizeof(void*));
    free(m_NodeData);
  }
  m_NodeData = static_cast<BlockInfo**>(newNodePointers);
  m_NodeData[m_BlockSize - 1] = static_cast<BlockInfo*>(newNodeData);

  for (int i = 0; i < m_BlockSize * BLOCK_PAGE_SIZE; ++i) {
    BlockInfo* newBlock = new((m_NodeData[m_BlockSize - 1] + i)) BlockInfo;
    newBlock->m_Next = m_UnusedBlocks;
    m_UnusedBlocks = newBlock;
  }
}


/******************************************************************************/
/*!
          FastAllocate

\author   John Salguero

\brief    Given an size to allocate, looks at the heap for the first available
          block usable and uses that to allocate the space

\param    bytes
          The size of the new allocation

\return   The pointer to the allocated space

*/
/******************************************************************************/
void* MemoryManager::FastAllocate(size_t bytes)
{
  void* allocated = nullptr;    /* memory in the heap to be returned */
  m_MemoryLock.lock();
  {
    BlockInfo* it = m_BlockList;  /* head of the list of nodes describing the memory available */

    /* crawl through the heap searching for the first fit */
    while (it)
    {
      /* if block is not free or adequate in size go to next block */
      if (it->m_Allocated || it->m_Size < bytes)
      {
        it = it->m_Next;
      }
      else /* if suitable block is found break */
      {
        break;
      }
    }
    /* if there is a suitable block insert an allocated block in the heap */
    if (it)
    {
      allocated = InsertBlock(it, bytes);
    }
    else 
    {
      throw std::bad_alloc();
    }
  } m_MemoryLock.unlock();

  return allocated;
}

/******************************************************************************/
/*!
          BestAllocate

\author   John Salguero

\brief    Given an size to allocate, looks at the heap for the best available
          block usable and uses that to allocate the space.

\param    bytes
          The size of the new allocation

\return   The pointer to the allocated space

*/
/******************************************************************************/
void* MemoryManager::BestAllocate(size_t bytes)
{
  void* allocated = nullptr;    /* memory in the heap to be returned */
  m_MemoryLock.lock(); {
    BlockInfo* bestFit = nullptr; /* free memory that best fits the size queried */
    BlockInfo* it = m_BlockList;  /* head of the list of nodes describing the memory available */

    /* crawl through the heap and find the best fit block */
    while (it)
    {
      /* if the current block is free and adequate in size */
      if (!(it->m_Allocated) && it->m_Size >= bytes)
      {
        if (!bestFit) /* if bestfit is null set it to the block */
        {
          bestFit = it;
          if (bestFit->m_Size == bytes) /* if a perfect match was found */
            break;
        }
        else /* if bestFit exists compare it to the current block */
        {
          if (bestFit->m_Size > it->m_Size) /* set bestFit to the smaller block */
          {
            bestFit = it;
            if (bestFit->m_Size == bytes) /* if a perfect match was found */
              break;
          }
        }
      }
      /* Crawl to the next block in the heap */
      it = it->m_Next;
    }
    /* if there is a best fit block insert an allocated block in the heap */
    if (bestFit)
    {
      allocated = InsertBlock(bestFit, bytes);
    }
    else {
      throw std::bad_alloc();
    }
  } m_MemoryLock.unlock();

  return allocated;
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
  BlockInfo* previous = nullptr; /* block before deallocated block */
  BlockInfo* delBlock;           /* block to be deleted */
  BlockInfo* it = m_BlockList;   /* iterator for the data heap */

  /* if the address exists determine if it can be deallocated */
  if (address)
  {
    /* crawl through the heap looking for the address specified */
    while (it && it->m_Address < (char*)address)
    {
      previous = it;
      it = it->m_Next;
    }

    /* if the address was found */
    if (it && it->m_Address == address)
    {
      m_MemoryLock.lock();
      /* deallocate the memory and consolidate surrounding free blocks */
      it->m_Allocated = false;
      /* Consolidate next block */
      if (it->m_Next && !(it->m_Next->m_Allocated))
      {
        delBlock = it->m_Next;
        it->m_Size += it->m_Next->m_Size;
        it->m_Next = it->m_Next->m_Next;
        delBlock->m_Next = m_UnusedBlocks;
        m_UnusedBlocks = delBlock;
      }
      /* Consolidate previous block */
      if (previous && !(previous->m_Allocated))
      {
        delBlock = it;
        previous->m_Size += it->m_Size;
        previous->m_Next = it->m_Next;
        delBlock->m_Next = m_UnusedBlocks;
        m_UnusedBlocks = delBlock;
      }
      m_MemoryLock.unlock();
    }
    else /* if the address was not found */
      return false;
  }

  return true;
}
