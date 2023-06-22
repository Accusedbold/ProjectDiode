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

Engine* Engine::m_Instance = new(static_cast<Engine*>(malloc(sizeof(Engine)))) Engine();

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
	return m_Instance;
}

/******************************************************************************/
/*!
          DestroyInstance

\author   John Salguero

\brief    Cleans up the instance of the engine by freeing the memoyr and calling
          it's destructor.

\return   whether the instance has been destroyed

*/
/******************************************************************************/
bool Engine::DestroyInstance()
{
  m_Instance->~Engine();
  free(m_Instance);
  return true;
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
  return false;
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
  int* stuff = new int[10];
  delete[] stuff;
  std::shared_ptr<int> counter(new int);
  do {
    ++*counter;
    if (*counter == 100)
      Close();
  } while (m_GameRunning);
	return 0;
}

/******************************************************************************/
/*!
          Close

\author   John Salguero

\brief    Initiates closing the game and the systems.

\return   Whether the game closed properly

*/
/******************************************************************************/
bool Engine::Close()
{
  m_GameRunning = false;
  return true;
}


