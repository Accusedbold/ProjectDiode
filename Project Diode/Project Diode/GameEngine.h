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
#ifndef GameEngine_H
#define GameEngine_H

// macros to make message system easy to use
#define RegisterClassListener(type, Class, fxn) \
{\
  void (Class::*def_member_)(std::shared_ptr<Message> const&) = fxn;\
  long long def_id_ = reinterpret_cast<long long>(this + reinterpret_cast<long&>(def_member_));\
  Callable def_fxn_(def_id_, std::bind(def_member_, this, std::placeholders::_1));\
  Engine::GetInstance()->RegisterListener(type, def_fxn_);\
}

#define RegisterGlobalListener(type, fxn) \
{\
  long long def_id_ = reinterpret_cast<long long>(fxn);\
  Callable def_fxn_(def_id_, std::bind(fxn, std::placeholders::_1));\
  Engine::GetInstance()->RegisterListener(type, def_fxn_);\
}

#define UnRegisterClassListener(type, Class, fxn) \
{\
  void (Class::*def_member_)(std::shared_ptr<Message> const&) = fxn;\
  long long def_id_ = reinterpret_cast<long long>(this + reinterpret_cast<long&>(def_member_));\
  Callable def_fxn_(def_id_, std::bind(def_member_, this, std::placeholders::_1));\
  Engine::GetInstance()->UnregisterListener(type, def_fxn_);\
}

#define UnRegisterGlobalListener(type, fxn) \
{\
  long long def_id_ = reinterpret_cast<long long>(fxn);\
  Callable def_fxn_(def_id_, std::bind(fxn, std::placeholders::_1));\
  Engine::GetInstance()->UnregisterListener(type, def_fxn_);\
}

class Engine {
  static Engine* m_Instance;
  bool m_GameRunning = true;

  Engine() = default;
  virtual ~Engine();

  // Adds all the Systems needed for running the game
  void AddSystems();
  // Initialize the Factory by adding all the component Factories
  void AddFactories();
  // Updates all the Systems this game tick
  void Update(double dt);
  // Broadcasts the Relayed messages
  void BroadcastMessages();

public:

  // Gets the singleton instance of the engine
  static Engine* GetInstance();
  // Destroys the engine
  static void DestroyInstance();

  // Initializes the Engine
  bool Inititialize();
  // The main loop of the game
  int GameLoop();
  // Closes down the game
  int Close();
  // Used to register a listener function
  void RegisterListener(MessageType, Callable const&);
  // Used to unregister a listener function
  void UnregisterListener(MessageType, Callable const&);
  // Adds a message to the queue of messages
  void RelayMessage(std::shared_ptr<Message> const&);
  // Broadcasts the message to handlers when called
  void ImmediateMessage(std::shared_ptr<Message> const&);

private:
  // mutex for the messages
  std::mutex m_MessageMutex;
  // vector for the new messages
  std::queue<std::shared_ptr<Message>> m_NewMessages;
  // Used As the messaging Handler for the game
  std::unordered_map < MessageType, std::list<Callable> >
    m_MessageHandlerMap;
  // Used to keep track of time intervals
  std::chrono::time_point<std::chrono::steady_clock> m_LastTime;
  // time since last frame
  std::chrono::duration<double, std::milli> m_TimeStep;
  // Tracks all the systems the game uses
  std::vector<std::shared_ptr<System>> m_Systems;
};

#endif
