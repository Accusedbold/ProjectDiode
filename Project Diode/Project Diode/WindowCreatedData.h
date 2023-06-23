/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    WindowCreatedData.h
  \author  John Salguero
  \date    June 23, 2023
  \brief
    This header file defines the Data for the Window Created Message
    which is used in response to certain actions, which send an event 
    when a new window is created that can be handled by systems such
    as graphics
*/
/********************************************************************/
#ifndef _WindowCreatedData
#define _WindowCreatedData

class WindowCreatedData {
public:
  //  Constructor
  WindowCreatedData(SDL_Window* window, int width, int height);

  // Default Destructor for Message Base Class
  virtual ~WindowCreatedData() = default;

  // Getters
  SDL_Window* GetWindow() const;
  int GetWidth() const;
  int GetHeight() const;

private:
  // the Window Context
  SDL_Window* m_Window;
  int m_Width;
  int m_Height;
};


#endif