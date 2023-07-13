/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    SlotMap.h
  \author  John Salguero
  \date    June 20, 2023
  \brief
    This header file declares the SlotMap class, which is a class that
    maintains objects, and allows fast allocation and lookup times

    This has been inspired by Allan Deutsch's talk at C++Now 2017
    Link: 
    https://www.youtube.com/watch?v=SHaAR7XPtNU&ab_channel=CppNow
*/
/********************************************************************/
#ifndef SlotMap_H
  #define SlotMap_H

#include "stdafx.h" // allocator

NOTE("TODO: Incomplete class, may not use")
template <class T, class Alloc = std::allocator<T>>
class SlotMap {
  // typedefs
  typedef T* pointer;

  size_t* m_Indices;
  void* m_Data;
  size_t* m_Erase;
  size_t* m_Freelist;
  size_t m_Size;

public:
  typedef unsigned SlotID;
  typedef T* SlotPointer;

  SlotMap(size_t size = 10) {
    m_Size = size;
  }

  SlotID getNewItemID(){

  }

  SlotPointer getNewItemPointer() {

  }

};

#endif
