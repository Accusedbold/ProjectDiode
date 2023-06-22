/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    MemoryManager.h
  \author  John Salguero
  \date    June 18, 2023
  \brief
    This header file declares the Allocator class, which is a class that
    allocates memory using malloc, so that the memory manager doesn't
    call global new, which in turn would use the memory manager to
    call global new, ad infinitum, causing a stack overflow

    This is taken from the example in the book
    "The C++ Standard Library"
*/
/********************************************************************/
#ifndef _Allocator
  #define _Allocator
#include "stdafx.h"

template <class T>
class Allocator {
public:
  // Type Definitions
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  // struct whose member other is an allocator
  // for the given class. This is used
  // in the STL allocators to allocate
  // other types using the given allocator
  template <class U> struct rebind {
    typedef Allocator<U> other;
  };


  /******************************************************************************/
  /*!
             address

  \author    John Salguero

  \brief     Return the address of object.

  \return    void

  */
  /******************************************************************************/
  pointer address(reference object) const {
    return &object;
  }

  /******************************************************************************/
  /*!
             address

  \author    John Salguero

  \brief     Return the address of a const object. (Const Correctness)

  \return    void

  */
  /******************************************************************************/
  const_pointer address(const_reference object) const {
    return &object;
  }

  /******************************************************************************/
  /*!
             Allocator

  \author    John Salguero

  \brief     Default Constructor

  \return    void

  */
  /******************************************************************************/
  Allocator() { }

  /******************************************************************************/
  /*!
             ~Mallocato

  \author    John Salguero

  \brief    Destructor

  \return    void

  */
  /******************************************************************************/
  ~Allocator() { }

  /******************************************************************************/
  /*!
             Allocator

  \author    John Salguero

  \brief     Const Copy Constructor

  \return    void

  */
  /******************************************************************************/
  Allocator(const Allocator&) { }

  /******************************************************************************/
  /*!
             Allocator

  \author    John Salguero

  \brief     Const Copy Constructor

  \return    void

  */
  /******************************************************************************/
  Allocator& operator=(const Allocator&) { return *this; }

  /******************************************************************************/
  /*!
             Allocator

  \author    John Salguero

  \brief     Const Copy Constructor that returns an Allocator of the same type,
             that is from something other than T.

  \return    void

  */
  /******************************************************************************/
  template <class U> Allocator(const Allocator<U>&) { }


  /******************************************************************************/
  /*!
             max_size

  \author    John Salguero

  \brief     This returns the maximum number of ELEMENTS that can be allocated.
             BIG * BIG = SMALL
             malloc(SMALL) will succeed

  \return    void

  */
  /******************************************************************************/
  size_type max_size() const {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
  }

  /******************************************************************************/
  /*!
             max_size

  \author    John Salguero

  \brief     This allocates the memory for num elements of type T

  \return    void

  */
  /******************************************************************************/
  pointer allocate(size_type num) {
    if (num == 0) { return nullptr; }

    if (num > max_size()) {
      // Too many elements
      // This check is to prevent the overflow:d
      throw std::length_error("Too Many Elements to Allocate");
    }

    void* ptr = malloc(num * sizeof(T));

    if (!ptr) {
      // malloc failed
      throw std::bad_alloc();
    }

    return static_cast<pointer>(ptr);
  }

  /******************************************************************************/
  /*!
             allocate

  \author    John Salguero

  \brief     We don't use the hint, we're only using malloc

  \return    void

  */
  /******************************************************************************/
  pointer allocate(const size_t n, const void* /*ignored*/) {
    return allocate(n);
  }

  /******************************************************************************/
  /*!
             max_size

  \author    John Salguero

  \brief     Free the previously allocated slot of memory

  \return    void

  */
  /******************************************************************************/
  void deallocate(pointer p, size_type /*ignored*/) {
    free(p);
  }

  /******************************************************************************/
  /*!
             construct

  \author    John Salguero

  \brief     Construct the new object by using placement new, which we are not
             overloading

  \return    void

  */
  /******************************************************************************/
  void construct(pointer p, const T& value) {
    new(static_cast<void*>(p)) T(value);
  }

  /******************************************************************************/
  /*!
             destroy

  \author    John Salguero

  \brief     Call the object's destructor

  \return    void

  */
  /******************************************************************************/
  void destroy(pointer p) {
    p->~T();
  }

};

template <class T1, class T2>
bool operator==(const Allocator<T1>&, const Allocator<T2>&) {
  return sizeof(T1) == sizeof(T2);
}

template <class T1, class T2>
bool operator!= (const Allocator<T1>&, const Allocator<T2>&) {
  return sizeof(T1) != sizeof(T2);
}

#endif