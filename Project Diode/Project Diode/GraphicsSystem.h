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
#ifndef GraphicsSystem_H
#define GraphicsSystem_H

#include "OpenGLDevice.h"



// System to handle and maintain the window state
class GraphicsSystem : public System, public std::enable_shared_from_this<GraphicsSystem> {
public:
  // Constructor
  GraphicsSystem(std::wstring& name);

  // Updates the function on a per frame basis
  void Update(double dt) override;

  // Releases the system and deletes all allocations
  int Release() override;

  // Initializes the system
  void Initialize() override;

private:
  // Function that handles a window created event
  void HandleWindowCreated(std::shared_ptr<Message> const& msg);
  // Function that handles creation of Renderables
  void HandleComponentCreated(std::shared_ptr<Message> const& msg);
  // Function that handles creation of Renderables
  void HandleComponentDestroyed(std::shared_ptr<Message> const& msg);
  // Draws the cameras not associated with a teleportal
  void DrawCameras();
  // Divides the renderables into batches the Device Uses
  std::unordered_map<long, std::multiset<std::shared_ptr<Renderable>>>
    DivideRenderables();

  // container owning window 
  SDL_Window* m_WindowHandle;
  // OpenGL device
  OpenGLDevice m_Device;
  // Holds All coliderless Renderables
  std::vector<std::weak_ptr<Renderable>> m_ColliderlessRenderables;
  // Holds All Cameras not part of a teleportal
  std::vector<std::weak_ptr<Camera>> m_Cameras;
};


#endif // !_GraphicsSystem

