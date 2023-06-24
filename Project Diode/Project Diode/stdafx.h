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
#define GLEW_STATIC // Using the static library compiled into the executable

// standard C library stuff
#include <memory>        // allocator
#include <vector>        // vector
#include <list>          // list
#include <limits>        // numeric_limits
#include <cstdlib>       // malloc
#include <stdexcept>     // length_error
#include <mutex>         // mutex
#include <string>        // memcpy_s
#include <functional>    // function
#include <queue>         // queue
#include <chrono>        // steady_clock, duration
#include <unordered_map> // unordered_map

// Engine stuff
#include "Debug.h"            // Used for logging and debugging 
#include "SDL\SDL.h"          // SDL2 library
#include "WindowDefines.h"    // FULLSCREEN_MODE, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE
#include "GL\glew.h"          // GLEW
#include "MemoryAllocation.h" // Global new overloading
#include "MemoryManager.h"    // Memory Manager 
#include "Callable.h"         // Callable
#include "MessageData.h"      // All the data types needed for the Message Types
#include "System.h"           // System
#include "GameEngine.h"       // Core of the game 
#include "Components.h"       // All the components
#include "Object.h"           // Object
#include "ComponentFactory.h" // ComponentFactory
#include "ObjectFactory.h"    // ObjectFactory

// Systems
#include "WindowSystem.h"     // WindowSystem
#include "GraphicsSystem.h"   // Graphics

// Utilities
#include "SlotMap.h"           // SlotMap 

#endif