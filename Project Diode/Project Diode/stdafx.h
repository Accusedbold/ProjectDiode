/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    stdafx.cpp
  \author  John Salguero
  \date    June 21, 2023
  \brief
    This is our header file including all precompiled code - include only
    those that change infrequently and or are widely used.
*/
/********************************************************************/
#ifndef _Precompiled
#define _Precompiled

// Values
#define GAME_HEAP_SIZE 2147483648
#define BLOCK_PAGE_SIZE 1000

// standard C library stuff
#include <memory>    // allocator
#include <vector>    // vector
#include <list>      // list
#include <limits>    // numeric_limits
#include <cstdlib>   // malloc
#include <stdexcept> // length_error
#include <mutex>     // mutex
#include <string>    // memcpy_s
#include <functional>// function

// Engine stuff
#include "Debug.h"            // Used for logging and debugging 
#include "MemoryAllocation.h" // Global new overloading
#include "MemoryManager.h"    // Memory Manager 
#include "Callable.h"         // Callable
#include "MessageData.h"      // All the data types needed for the Message Types
#include "GameEngine.h"       // Core of the game 
#include "SDL\SDL.h"          // SDL2 library

// Utilities
#include "SlotMap.h"           // SlotMap 

#endif