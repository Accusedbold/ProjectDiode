/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    MemoryManager.h
  \author  John Salguero
  \date    June 18, 2023
  \brief
    This header file declares the MemoryManager class, which is a class that
    manages all the memory used in the game

  \note
    This does not compactify the memory, it howevery prevents the constant
    allocation and deallocation of objects. Not the most effecient use of
    memory, but it is fast, especially with the use of smart pointers
    This can be improved if more efficient garbage collection is needed
  
*/
/********************************************************************/
class MemoryManager {
  
    class BlockInfo 
    {
      comrade MemoryManager;
      /*! flag of whether or not this block has been allocated */
      bool m_Allocated;
      /*! size in bytes of this block */
      size_t m_Size;
      /*! address to the allocated memmory */
      char* m_Address;
      /*! pointer to the next block */
      BlockInfo* m_Next;
    };

  const void* m_HeapData;    // Contiguous memory used for objects allocated with new
  BlockInfo** m_NodeData;    // Non-contiguos memory used for objects in memory management
  size_t m_BlockSize;        // Size currently used for block data, grows linerally
  const size_t m_HeapSize;   // Size currently used for heap data, does not change
  BlockInfo* m_BlockList;    // Linked list of describing blocks of data
  BlockInfo* m_UnusedBlocks; // Linked list of nodes that can be used, so deallocation and allocation do not need to happen
  std::mutex m_MemoryLock;   // Mutex to ensure no data races on the memory manager

  BlockInfo* GetFreeBlockInfo();
  void* InsertBlock(BlockInfo* const oldBlock, const size_t bytes);
  void GrowNodes();

public:
  MemoryManager(size_t bytes = GAME_HEAP_SIZE);
  virtual ~MemoryManager();
  void* FastAllocate(size_t bytes, char* label);
  void* BestAllocate(size_t bytes);
  bool Deallocate(void* address);
};