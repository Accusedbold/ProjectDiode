/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Engine.h
  \author  John Salguero
  \date    June 18, 2023
  \brief
    This header file declares the Engine class, which is a class that drives the
    messaging system, game loop and updates each system accordingly
*/
/********************************************************************/
#ifndef _GameEngine
	#define _GameEngine

// macros to make message system easy to use
#define RegisterClassListener(type, Class, fxn) \
{\
  void (Class::*def_member_)(std::shared_ptr<Message> const&) = fxn;\
  long def_id_ = reinterpret_cast<long>(this + reinterpret_cast<long&>(def_member_));\
  Callable def_fxn_(def_id_, std::bind(def_member_, this, std::placeholders::_1));\
  Engine::RegisterListener(type, def_fxn_);\
}

#define RegisterGlobalListener(type, fxn) \
{\
  long def_id_ = reinterpret_cast<long>(fxn);\
  Callable def_fxn_(def_id_, std::bind(fxn, std::placeholders::_1));\
  Engine::RegisterListener(type, def_fxn_);\
}

#define UnRegisterClassListener(type, Class, fxn) \
{\
  void (Class::*def_member_)(std::shared_ptr<Message> const&) = fxn;\
  long def_id_ = reinterpret_cast<long>(this + reinterpret_cast<long&>(def_member_));\
  Callable def_fxn_(def_id_, std::bind(def_member_, this, std::placeholders::_1));\
  Engine::UnregisterListener(type, def_fxn_);\
}

#define UnRegisterGlobalListener(type, fxn) \
{\
  long def_id_ = reinterpret_cast<long>(fxn);\
  Callable def_fxn_(def_id_, std::bind(fxn, std::placeholders::_1));\
  Engine::UnregisterListener(type, def_fxn_);\
}

class Engine {
  static Engine* m_Instance;
  MemoryManager m_MemoryManager;
  bool m_GameRunning = true;

  Engine() = default;
  virtual ~Engine();

public:

  // Gets the singleton instance of the engine
  static Engine* GetInstance();
  // Destroys the engine
  static bool DestroyInstance();

  // Initializes the Engine
  bool Inititialize();
  // The main loop of the game
  int GameLoop();
  // Closes down the game
  bool Close();
  // Used to register a listener function
  static void RegisterListener(MessageType, Callable const&);
  // Used to unregister a listener function
  static void UnregisterListener(MessageType, Callable const&);
 
  // These global functions are necessary to access the  Memory Manager
  comrade void* operator new(size_t size) noexcept(false);
  comrade void* operator new(size_t size, const std::nothrow_t&) noexcept(true);
  comrade void* operator new[](size_t size) noexcept(false);
  comrade void* operator new[](size_t size, const std::nothrow_t&) noexcept(true);
   
  comrade void operator delete(void* ptr) noexcept(true);
  comrade void operator delete(void* ptr, const std::nothrow_t&) noexcept(true);
  comrade void operator delete[](void* ptr) noexcept(true);
  comrade void operator delete[](void* ptr, const std::nothrow_t&) noexcept(true);
};

#endif
