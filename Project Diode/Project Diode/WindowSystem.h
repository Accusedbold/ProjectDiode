/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    WindowSystem.h
  \author  John Salguero
  \date    June 21, 2023
  \brief
    This header file declares the the WindowSystem Class which
    is used to manage the events and the operating systems windows
*/
/********************************************************************/
#ifndef WindowSystem_H
#define WindowSystem_H

// System to handle and maintain the window state
class WindowSystem : public System, public std::enable_shared_from_this<WindowSystem>{
public:
  // Constructor
  WindowSystem(std::wstring& name);

  // Updates the function on a per frame basis
  virtual void Update(double dt);

  // Releases the system and deletes all allocations
  virtual int Release();

  // Initializes the system
  virtual void Initialize();

private:

  void HandleEvents();

  // Creates an error popup message box
  void ErrorPopUp(std::shared_ptr<Message> const& msg);

  // Creates an popup message box
  void PopUp(std::shared_ptr<Message> const& msg);

  // Window Size
  int m_Width = WINDOW_WIDTH;
  int m_Height = WINDOW_HEIGHT;

  // Window Location
  unsigned m_PosX = 100;
  unsigned m_PosY = 100;

  // Window descriptors
  char const* m_WinTitle = WINDOW_TITLE;
  bool m_FullScreen = FULLSCREEN_MODE;
  unsigned m_WinFlags;

  // Graphics stuff
  SDL_Window* m_Window = nullptr;
  SDL_Surface* m_WindowSurface = nullptr;

};

#endif
