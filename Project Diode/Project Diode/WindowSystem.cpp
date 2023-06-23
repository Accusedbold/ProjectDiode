/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    WindowSystem.cpp
  \author  John Salguero
  \date    June 21, 2023
  \brief
    This cpp file deifines the member functions for the WindowSystem
    Class, which is used to manage the events and the operating
    systems windows
*/
/********************************************************************/
#include "stdafx.h"

/******************************************************************************/
/*!
           WindowSystem

\author    John Salguero

\brief     Default constructor for the Window System

*/
/******************************************************************************/
WindowSystem::WindowSystem(std::wstring& name) : System(name)
{
  if (m_FullScreen)
    m_WinFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
  else
    m_WinFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
}

/******************************************************************************/
/*!
            Initialize

\author     John Salguero

\brief      Initializes the windows system for the game, creates the windows
            using SDL2

\return     void
*/
/******************************************************************************/
void WindowSystem::Initialize()
{
  // Register the listener for Error Messages
	RegisterClassListener(MessageType::ErrorMessage, WindowSystem, &WindowSystem::ErrorPopUp);

  // Initialize SDL for video and Errorcheck
  FATAL_ERRORIF(SDL_Init(SDL_INIT_VIDEO) < 0, std::string("SDL could not be properly initialized.\nSDL_Error: ") + SDL_GetError());

  // Create The Window and Errorcheck
  m_Window = SDL_CreateWindow(m_WinTitle, m_PosX, m_PosY, m_Width, m_Height, m_WinFlags);
  FATAL_ERRORIF(!m_Window, std::string("Window could not properly be created.\nSDL_Error: ") + SDL_GetError());

  SDL_Surface* icon = SDL_LoadBMP("Textures\\diode.bmp");
  ERRORIF(!icon, "Failed to load icon " + std::string(SDL_GetError()));

  SDL_SetWindowIcon(m_Window, icon);
  SDL_FreeSurface(icon);

  Engine::GetInstance()->RelayMessage(std::shared_ptr<Message>(
    new Message(m_SystemName, MessageType::WindowCreated, std::shared_ptr<void>(
      new WindowCreatedData(m_Window, m_Width, m_Height)))));

  return;

}

/******************************************************************************/
/*!
            Update

\author     John Salguero

\brief      Updates the System every game tic. Handles the windows events

\param      double
            The time step of the game- this is ignored

\return     void
*/
/******************************************************************************/
void WindowSystem::Update(double)
{
  HandleEvents();
}

/******************************************************************************/
/*!
            Release

\author     John Salguero

\brief      Releases, and shuts down all that it has created

\return     int
            Error code upon releasing resources. 0 is success
*/
/******************************************************************************/
int WindowSystem::Release()
{
  // Unregister the listener class since it can no longer handle messages
	UnRegisterClassListener(MessageType::ErrorMessage, WindowSystem, &WindowSystem::ErrorPopUp);

  // Destroy The Window and clean up the surface
  SDL_DestroyWindow(m_Window);

  // Quit SDL_VIDEO Subsystem
  SDL_QuitSubSystem(SDL_INIT_VIDEO);

	return 0;
}

/******************************************************************************/
/*!
            HandleEvents

\author     John Salguero

\brief      Handles the windows events, allows for the user to fullscreen,
            exit, move, resize, etc

\return     void
*/
/******************************************************************************/
void WindowSystem::HandleEvents()
{
  // Event handler
  SDL_Event event;
  SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);

  // Handle events on queue
  while (SDL_PollEvent(&event) != 0)
  {
    // switch of the event types
    switch (event.type)
    {
      //User requests quit
    case SDL_QUIT:
      Engine::GetInstance()->RelayMessage(std::shared_ptr<Message>(new Message(m_SystemName, MessageType::Quit, nullptr)));
      break;
    case SDL_SYSWMEVENT:
      //HandleWMEvents(event.syswm.msg->msg.win.msg, event.syswm.msg->msg.win.wParam, event.syswm.msg->msg.win.lParam);
      break;
    default:
      break;
    }
  }
}

/******************************************************************************/
/*!
            ErrorPopUp

\author     John Salguero

\brief      Given an error message, will popup with a message and give
            specifics on that error.

\param      msg
            The error message given to the user.

\return     void
*/
/******************************************************************************/
void WindowSystem::ErrorPopUp(std::shared_ptr<Message> const& msg)
{
  std::string winMessage;
  std::string winTitle;

  auto data = GET_DATA_FROM_MESSAGE(ErrorMessageData, msg);

  if (data->GetIsFatal())
    winTitle = "Fatal Error";
  else
    winTitle = "Error";

  winMessage = data->GetErrorMessage() + "\nSource File: " + data->GetSourceFile()
    + "\nLine Number: " + std::to_string(data->GetLineNum()) + "\n Function Name: " + data->GetFuncName();

  int error;
  error = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, winTitle.data(), winMessage.data(), m_Window);
  if (error)
    exit(ERROR_WINDOW_FAILED);

  if (data->GetIsFatal())
    exit(FATAL_RUNTIME_ERROR);
  else
    DEBUGME();
}
