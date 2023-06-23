/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    GameEngine.cpp
  \author  John Salguero
  \date    June 18, 2023
  \brief
    This cpp file defines the Engine class functions, which is a class that drives the
    messaging system, game loop and updates each system accordingly
*/
/********************************************************************/
#include "stdafx.h" // Engine, shared_ptr

Engine* Engine::m_Instance = nullptr;

/******************************************************************************/
/*!
          ~Engine

\author   John Salguero

\brief    Destructor for the game engine. Makes sure the game closes if it is
          being destroyed

*/
/******************************************************************************/
Engine::~Engine() {
  if (m_GameRunning)
    Close();
}

/******************************************************************************/
/*!
          AddSystems

\author   John Salguero

\brief    Adds the systems needed for running the game

*/
/******************************************************************************/
void Engine::AddSystems()
{
  std::wstring name(L"Graphics System");
  m_Systems.push_back(std::shared_ptr<GraphicsSystem>(new GraphicsSystem(name)));

  name = L"Windows System";
  m_Systems.push_back(std::shared_ptr<WindowSystem>(new WindowSystem(name)));
}

/******************************************************************************/
/*!
          Update

\author   John Salguero

\brief    Updates the systems needed for running the game every game tic

*/
/******************************************************************************/
void Engine::Update(double dt)
{
  for (auto it = m_Systems.begin(), end = m_Systems.end(); it != end; ++it) {
    (*it)->Update(dt);
  }
}

/******************************************************************************/
/*!
          GetInstance

\author   John Salguero

\brief    Returns a pointer to a singleton object of the Engine. There should
          only be 1 instance, which is why the constructor is private. This
          is static, so it can be used if no instance exists yet.

\return   The pointer to the singleton instance of the Game engine

*/
/******************************************************************************/
Engine* Engine::GetInstance()
{
  if (!m_Instance)
    m_Instance = new Engine;
	return m_Instance;
}

/******************************************************************************/
/*!
          DestroyInstance

\author   John Salguero

\brief    Cleans up the instance of the engine by freeing the memoyr and calling
          it's destructor.

\return   void

*/
/******************************************************************************/
void Engine::DestroyInstance()
{
  if(m_Instance)
    delete m_Instance;
}

/******************************************************************************/
/*!
          Inititialize

\author   John Salguero

\brief    Initializes The game engine and its systems.

\return   whether the game successfully initialized

*/
/******************************************************************************/
bool Engine::Inititialize()
{
  // Add everything
  AddSystems();
  // Initialize Everything
  for (auto it = m_Systems.begin(), end = m_Systems.end(); it != end; ++it)
    (*it)->Initialize();

  return true;
}

/******************************************************************************/
/*!
          GameLoop

\author   John Salguero

\brief    The main game loop.

\return   Error code. 0 means it exited safely

*/
/******************************************************************************/
int Engine::GameLoop()
{
  m_LastTime = std::chrono::steady_clock::now();
  double counter = 0;
  do {
    auto currentTime = std::chrono::steady_clock::now();
    m_TimeStep = currentTime - m_LastTime;
    m_LastTime = currentTime;
    counter += m_TimeStep.count();
    Update(counter);
  } while (m_GameRunning);

	return Close();
}

/******************************************************************************/
/*!
          Close

\author   John Salguero

\brief    Initiates closing the game and the systems.

\return   The error code upon closing the systems

*/
/******************************************************************************/
int Engine::Close()
{
  int retVal = 0;
  m_GameRunning = false;
  for (auto it = m_Systems.begin(), end = m_Systems.end(); it != end; ++it)
    (*it)->Release() ? retVal = SYSTEM_RELEASE_ERROR : retVal = retVal;
  return retVal;
}

/******************************************************************************/
/*!
          RegisterListener

\author   John Salguero

\brief    Given the Message type and the handler, adds the handler to the map of
          message handlers.

\param    type
          The message type to be handled

\param    fxn
          The Callable that handles that message type

\return   void

*/
/******************************************************************************/
void Engine::RegisterListener(MessageType type, Callable const& fxn)
{
  m_MessageHandlerMap[type].push_back(fxn);
}

/******************************************************************************/
/*!
          UnregisterListener

\author   John Salguero

\brief    Given the Message type and the handler, removes the handler to the map of
          message handlers. This should be used by any handler that is destroyed
          or becomes inaccessable.

\param    type
          The message type to be handled

\param    fxn
          The Callable that handles that message type

\return   void

*/
/******************************************************************************/
void Engine::UnregisterListener(MessageType type, Callable const& fxn)
{
  m_MessageHandlerMap[type].remove(fxn);
}

/******************************************************************************/
/*!
          ImmediateMessage

\author   John Salguero

\brief    Message that is immediately handled.

\return   void

*/
/******************************************************************************/
void Engine::ImmediateMessage(std::shared_ptr<Message> const& msg)
{
  // This code goes through all the registered functions on the list and sends the appropriate message to them
  auto functionList = m_MessageHandlerMap[msg->GetMessageId()];

  for (auto nit = functionList.begin(), it = functionList.begin(); it != functionList.end();)
  {
    ++nit;
    (*it)(msg);
    it = nit;
  }
}

/******************************************************************************/
/*!
          RelayMessage

\author   John Salguero

\brief    Relays a message to be handled at the end of the game loop.

\return   void

*/
/******************************************************************************/
void Engine::RelayMessage(std::shared_ptr<Message> const& msg)
{
  m_MessageMutex.lock();
  m_NewMessages.push(msg);
  m_MessageMutex.unlock();

  if (msg->GetMessageId() == MessageType::Quit)
  {
    Close();
  }
}

/******************************************************************************/
/*!
          BroadcastMessages

\author   John Salguero

\brief    Every Game loop broadcasts the relayed messages.

\return   void

*/
/******************************************************************************/
void Engine::BroadcastMessages()
{
  // empty out the messages
  while (!m_NewMessages.empty())
  {
    const std::shared_ptr<Message> &msg = m_NewMessages.front();
    auto functionList = m_MessageHandlerMap[msg->GetMessageId()];

    for (auto nit = functionList.begin(), it = functionList.begin(); it != functionList.end();)
    {
      ++nit;
      (*it)(msg);
      it = nit;
    }

    m_MessageMutex.lock();
    m_NewMessages.pop();
    m_MessageMutex.unlock();
  }
}



