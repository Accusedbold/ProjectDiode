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
    m_WinFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
  else
    m_WinFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
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
  // Register the listener for Popup Messages
  RegisterClassListener(MessageType::PopUp, WindowSystem, &WindowSystem::PopUp);

  // Initialize SDL for video and Errorcheck
  FATAL_ERRORIF(SDL_Init(SDL_INIT_VIDEO) < 0, std::string("SDL could not be properly initialized.\nSDL_Error: ") + SDL_GetError());

  // Set the Depth Buffer Precision
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, DEPTH_BUFFER_SIZE);

  // Create The Window and Errorcheck
  m_Window = SDL_CreateWindow(m_WinTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, m_WinFlags);
  FATAL_ERRORIF(!m_Window, std::string("Window could not properly be created.\nSDL_Error: ") + SDL_GetError());

  SDL_Surface* icon = SDL_LoadBMP("Resources\\Textures\\diode.bmp");
  ERRORIF(!icon, "Failed to load icon " + std::string(SDL_GetError()));

  SDL_SetWindowIcon(m_Window, icon);
  SDL_FreeSurface(icon);

  // Set the capture of Relative mouse motion
  SDL_SetRelativeMouseMode(SDL_TRUE);

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
  UnRegisterClassListener(MessageType::PopUp, WindowSystem, &WindowSystem::PopUp);

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
    case SDL_WINDOWEVENT:
      HandleWindowEvents(event.window);
      break;
    case SDL_KEYDOWN:
    case SDL_KEYUP:
    case SDL_TEXTEDITING:
    case SDL_TEXTINPUT:
    case SDL_KEYMAPCHANGED:
    case SDL_MOUSEMOTION:
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEWHEEL:
    case SDL_JOYAXISMOTION:
    case SDL_JOYBALLMOTION:
    case SDL_JOYHATMOTION:
    case SDL_JOYBUTTONDOWN:
    case SDL_JOYBUTTONUP:
    case SDL_JOYDEVICEADDED:
    case SDL_JOYDEVICEREMOVED:
    case SDL_JOYBATTERYUPDATED:
    case SDL_CONTROLLERAXISMOTION:
    case SDL_CONTROLLERBUTTONDOWN:
    case SDL_CONTROLLERBUTTONUP:
    case SDL_CONTROLLERDEVICEADDED:
    case SDL_CONTROLLERDEVICEREMOVED:
    case SDL_CONTROLLERDEVICEREMAPPED:
    case SDL_CONTROLLERTOUCHPADDOWN:
    case SDL_CONTROLLERTOUCHPADMOTION:
    case SDL_CONTROLLERTOUCHPADUP:
    case SDL_CONTROLLERSENSORUPDATE:
      Engine::GetInstance()->RelayMessage(std::shared_ptr<Message>(new Message(m_SystemName, MessageType::Input, std::shared_ptr<void>(new SDL_Event(event)))));
      break;
    default:
      break;
    }
  }
}

/******************************************************************************/
/*!
            HandleWindowEvents

\author     John Salguero

\brief      Given a windows event, handles what happens

\param      event
            The event to handle

\return     void
*/
/******************************************************************************/
void WindowSystem::HandleWindowEvents(SDL_WindowEvent const& event)
{
  switch (event.event) {
  case SDL_WINDOWEVENT_SHOWN:
    SDL_Log("Window %d shown", event.windowID);
    break;
  case SDL_WINDOWEVENT_HIDDEN:
    SDL_Log("Window %d hidden", event.windowID);
    break;
  case SDL_WINDOWEVENT_EXPOSED:
    SDL_Log("Window %d exposed", event.windowID);
    break;
  case SDL_WINDOWEVENT_MOVED:
    SDL_Log("Window %d moved to %d,%d",
      event.windowID, event.data1,
      event.data2);
    break;
  case SDL_WINDOWEVENT_RESIZED:
    Engine::GetInstance()->RelayMessage(std::shared_ptr<Message>(new Message(m_SystemName, MessageType::WindowResized, std::shared_ptr<void>(new SDL_WindowEvent(event)))));
    break;
  case SDL_WINDOWEVENT_SIZE_CHANGED:
    SDL_Log("Window %d size changed to %dx%d",
      event.windowID, event.data1,
      event.data2);
    break;
  case SDL_WINDOWEVENT_MINIMIZED:
    SDL_Log("Window %d minimized", event.windowID);
    break;
  case SDL_WINDOWEVENT_MAXIMIZED:
    SDL_Log("Window %d maximized", event.windowID);
    break;
  case SDL_WINDOWEVENT_RESTORED:
    SDL_Log("Window %d restored", event.windowID);
    break;
  case SDL_WINDOWEVENT_ENTER:
    SDL_Log("Mouse entered window %d",
      event.windowID);
    break;
  case SDL_WINDOWEVENT_LEAVE:
    SDL_Log("Mouse left window %d", event.windowID);
    break;
  case SDL_WINDOWEVENT_FOCUS_GAINED:
    SDL_Log("Window %d gained keyboard focus",
      event.windowID);
    break;
  case SDL_WINDOWEVENT_FOCUS_LOST:
    SDL_Log("Window %d lost keyboard focus",
      event.windowID);
    break;
  case SDL_WINDOWEVENT_CLOSE:
    SDL_Log("Window %d closed", event.windowID);
    break;
  case SDL_WINDOWEVENT_TAKE_FOCUS:
    SDL_Log("Window %d is offered a focus", event.windowID);
    break;
  case SDL_WINDOWEVENT_HIT_TEST:
    SDL_Log("Window %d has a special hit test", event.windowID);
    break;
  default:
    SDL_Log("Window %d got unknown event %d",
      event.windowID, event.event);
    break;
  }
}

/******************************************************************************/
/*!
            PopUp

\author     John Salguero

\brief      Given a message, will popup with the message and give.

\param      msg
            The error message given to the user.

\return     void
*/
/******************************************************************************/
void WindowSystem::PopUp(std::shared_ptr<Message> const& msg)
{
  std::string winMessage;
  std::string winTitle;

  auto data = GET_DATA_FROM_MESSAGE(PopUpMessageData, msg);

  winTitle = "Message";

  winMessage = data->GetMessage();

  int error;
  error = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, winTitle.data(), winMessage.data(), m_Window);
  if (error)
    exit(ERROR_WINDOW_FAILED);
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
