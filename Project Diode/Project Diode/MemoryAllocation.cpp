/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    MemoryAllocation.h
  \author  John Salguero
  \date    June 18, 2023
  \brief
    This cpp file defines the global new and delete functions,
    which manages all the memory used in the game
*/
/********************************************************************/
#include "stdafx.h"

/******************************************************************************/
/*!
          new

\author   John Salguero

\brief    overloads the gloabal new operator so that everytime the new
          operator is used to allocate memory, it goes through the memory
          manager.

\param    size
          The size of the allocation

\return   The pointer to the allocated space

*/
/******************************************************************************/
void* operator new(size_t size) noexcept(false)
{
  return MemoryManager::GetInstance()->BestAllocate(size);
}

/******************************************************************************/
/*!
          new

\author   John Salguero

\brief    overloads the gloabal new operator so that everytime the new
          operator is used to allocate memory, it goes through the memory
          manager.

\param    size
          The size of the allocation

\param    std::nothrow_t&
          Indicates this function does not throw

\return   The pointer to the allocated space

*/
/******************************************************************************/
void* operator new(size_t size, const std::nothrow_t&) noexcept(true)
{
  try {
    return MemoryManager::GetInstance()->BestAllocate(size);
  }
  catch (std::bad_alloc ex) {
    return nullptr;
  }
}

/******************************************************************************/
/*!
          new[]

\author   John Salguero

\brief    overloads the gloabal new operator so that everytime the new
          operator is used to allocate memory, it goes through the memory
          manager.

\param    size
          The size of the allocation

\return   The pointer to the allocated space

*/
/******************************************************************************/
void* operator new[](size_t size) noexcept(false)
{
  return MemoryManager::GetInstance()->BestAllocate(size);
}


/******************************************************************************/
/*!
          new[]

\author   John Salguero

\brief    overloads the gloabal new operator so that everytime the new
          operator is used to allocate memory, it goes through the memory
          manager.

\param    size
          The size of the allocation

\param    std::nothrow_t&
          Indicates this function does not throw

\return   The pointer to the allocated space

*/
/******************************************************************************/
void* operator new[](size_t size, const std::nothrow_t&) noexcept(true)
{
  try {
    return MemoryManager::GetInstance()->BestAllocate(size);
  }
  catch (std::bad_alloc ex) {
    return nullptr;
  }
}

/******************************************************************************/
/*!
          delete

\author   John Salguero

\brief    overloads the gloabal delete operator so that everytime the delete
          operator is used to deallocate memory, it goes through the memory
          manager.

\param    ptr
          The pointer of the allocated memory to deallocate


\return   void

*/
/******************************************************************************/
void operator delete(void* ptr) noexcept(true)
{
  MemoryManager::GetInstance()->Deallocate(ptr);
}

/******************************************************************************/
/*!
          delete

\author   John Salguero

\brief    overloads the gloabal delete operator so that everytime the delete
          operator is used to deallocate memory, it goes through the memory
          manager.

\param    ptr
          The pointer of the allocated memory to deallocate

\param    std::nothrow_t&
          Indicates this function does not throw

\return   void

*/
/******************************************************************************/
void operator delete(void* ptr, const std::nothrow_t&) noexcept(true)
{
  MemoryManager::GetInstance()->Deallocate(ptr);
}

/******************************************************************************/
/*!
          delete[]

\author   John Salguero

\brief    overloads the gloabal delete operator so that everytime the delete
          operator is used to deallocate memory, it goes through the memory
          manager.

\param    ptr
          The pointer of the allocated memory to deallocate

\return   void

*/
/******************************************************************************/
void operator delete[](void* ptr) noexcept(true)
{
  MemoryManager::GetInstance()->Deallocate(ptr);
}

/******************************************************************************/
/*!
          delete[]

\author   John Salguero

\brief    overloads the gloabal delete operator so that everytime the delete
          operator is used to deallocate memory, it goes through the memory
          manager.

\param    ptr
          The pointer of the allocated memory to deallocate

\param    std::nothrow_t&
          Indicates this function does not throw

\return   void

*/
/******************************************************************************/
void operator delete[](void* ptr, const std::nothrow_t&) noexcept(true)
{
  MemoryManager::GetInstance()->Deallocate(ptr);
}
