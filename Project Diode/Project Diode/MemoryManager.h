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


using type_ptr = unsigned long long;

class MemoryManager {

  struct BlockInfo
  {
    /*! pointer to the next block */
    BlockInfo* m_Next;
  };

public:
  // constructor - decides the heap size upon construction
  MemoryManager(size_t bytes = GAME_HEAP_SIZE);
  // destructor - frees all the memory
  virtual ~MemoryManager();
  // Gets the instance of the Memory Manager
  static MemoryManager* GetInstance();
  // Destroys the instance of the Memory Manager
  static void DestroyInstance();
  // Allocates by using the first memory available - tends to fragment
  void* Allocate(size_t bytes);
  // Deletes the allocated memory
  bool Deallocate(void* address);

private:
  static MemoryManager* m_Instance; // Instance of the MemoryManager
  const void* m_HeapData;           // Contiguous memory used for objects allocated with new
  BlockInfo** m_NodeData;           // Non-contiguos memory used for objects in memory management
  size_t m_BlockSize;               // Size currently used for block data, grows linerally
  const size_t m_HeapSize;          // Size currently used for heap data, does not change
  BlockInfo* m_BlockList;           // Linked list of describing blocks of data
  BlockInfo* m_UnusedBlocks;        // Linked list of nodes that can be used, so deallocation and allocation do not need to happen
  std::mutex m_MemoryLock;          // Mutex to ensure no data races on the memory manager

  // allocates and adds block nodes to the list of free block nodes
  void GetNextBlock(size_t size, type_ptr& begin, type_ptr& end);

  // These global functions are necessary to access the  Memory Manager
  comrade void* operator new(size_t size) noexcept(false);
  comrade void* operator new(size_t size, const std::nothrow_t&) noexcept(true);
  comrade void* operator new[](size_t size) noexcept(false);
  comrade void* operator new[](size_t size, const std::nothrow_t&) noexcept(true);

  comrade void operator delete(void* ptr) noexcept(true);
  comrade void operator delete(void* ptr, const std::nothrow_t&) noexcept(true);
  comrade void operator delete[](void* ptr) noexcept(true);
  comrade void operator delete[](void* ptr, const std::nothrow_t&) noexcept(true);

  template<size_t size> comrade class MemorySlotMap;
};