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

Engine::Engine() {
  m_GameRunning = true;
}

Engine::~Engine() {
  if (m_GameRunning)
    Close();
}

Engine* Engine::GetInstance()
{
	return m_Instance;
}

bool Engine::DestroyInstance()
{
  m_Instance->~Engine();
  free(m_Instance);
  return true;
}

bool Engine::Inititialize()
{
  return false;
}

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

bool Engine::Close()
{
  m_GameRunning = false;
  return true;
}


