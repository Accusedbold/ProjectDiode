/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    GraphicsSystem.h
  \author  John Salguero
  \date    June 23, 2023
  \brief
    This header file defines the Graphics System class, which is
    a class that drives the Underlying Graphics of the Game
*/
/********************************************************************/
#ifndef _GraphicsSystem
#define _GraphicsSystem

#include "OpenGLDevice.h"

// System to handle and maintain the window state
class GraphicsSystem : public System, public std::enable_shared_from_this<GraphicsSystem> {
public:
  // Constructor
  GraphicsSystem(std::wstring& name);

  // Updates the function on a per frame basis
  virtual void Update(double dt);

  // Releases the system and deletes all allocations
  virtual int Release();

  // Initializes the system
  virtual void Initialize();

private:
  // Function that handles a window created event
  void HandleWindowCreated(std::shared_ptr<Message> const& msg);

  // container owning window 
  SDL_Window* m_WindowHandle;
  // OpenGL device
  OpenGLDevice m_Device;
};


#endif // !_GraphicsSystem

