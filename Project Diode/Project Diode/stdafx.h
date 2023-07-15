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
#ifndef Precompiled_H
#define Precompiled_H

// Values
#define GAME_HEAP_SIZE 2147483648
#define BLOCK_PAGE_SIZE 1000
#define GLEW_STATIC // Using the static library compiled into the executable

// standard C library stuff
#include <memory>          // allocator
#include <type_traits>     // is_same
#include <vector>          // vector
#include <set>             // set, multimap
#include <list>            // list
#include <limits>          // numeric_limits
#include <cstdlib>         // malloc
#include <stdexcept>       // length_error
#include <mutex>           // mutex
#include <string>          // memcpy_s
#include <functional>      // function
#include <chrono>          // steady_clock, duration
#include <queue>           // queue
#include <unordered_map>   // unordered_map
#include <map>             // multimap
#include <filesystem>      // path, exists, is_directory, directory_iterator
#include <fstream>         // ofstream
#include <GL\glew.h>       // GLEW
#include <glm\glm.hpp>     // glm Math library
#include <SDL\SDL.h>       // SDL2 library
#include <SDL\SDL_image.h> // SDL Image

namespace fs = std::filesystem;

// Engine stuff
#include "Debug.h"            // Used for logging and debugging 
#include "Serialization.h"    // Used for serializing
#include "shaders.h"          // Shader enums
#include "ResourceTypes.h"    // Differnt Types of Resources
#include "Resource.h"         // The interface to the resources
#include "ResourceLoader.h"   // ResourceLoader
#include "ResourceManager.h"  // ResourceManager
#include "WindowDefines.h"    // FULLSCREEN_MODE, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE
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
#include "MemorySlotMap.h"    // MemorySlotMap

// Systems
#include "Systems.h"          // All The Systems the Game uses

// Utilities
#include "SlotMap.h"             // SlotMap 
#include "QuaternionTransform.h" // Custom Class made to interpolate between animation
#include "Comparators.h"         // Funtors for organizing containers

#endif