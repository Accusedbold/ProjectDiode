/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    OpenGLDevice.cpp
  \author  John Salguero
  \date    June 23, 2023
  \brief
    This cpp file defines the OpenGL Device class, which is
    a class that drives the opengl behavior of the game,
    that is - it executes the low level graphics calls
*/
/********************************************************************/
#include "stdafx.h"

/******************************************************************************/
/*!
          InitializedUpdate

\author   John Salguero

\brief    The Update function after the device is properly initialized

\param    dt
          The delta in time since last game tick

\return   void
*/
/******************************************************************************/
void OpenGLDevice::InitializedUpdate(double)
{
}

/******************************************************************************/
/*!
          DoNothing

\author   John Salguero

\brief    The update function before the device is initialized.

\param    double
          The delta in time since last game tick(ignored)

\return   void
*/
/******************************************************************************/
void OpenGLDevice::DoNothing(double)
{
}

/******************************************************************************/
/*!
          Update

\author   John Salguero

\brief    The function called every game tick. uses a function pointer to stop
          using an if check every game tick

\param    dt
          The delta in time since last game tick

\return   void
*/
/******************************************************************************/
void OpenGLDevice::Update(double dt)
{
  (this->*m_UpdateFxn)(dt);
}

/******************************************************************************/
/*!
          Initialize

\author   John Salguero

\brief    Given a WindowCreatedData pointer, initializes the glDevice.

\param    msgData
          The Data that comes with window creation

\return   void
*/
/******************************************************************************/
bool OpenGLDevice::Initialize(std::shared_ptr<WindowCreatedData> const& msgData)
{
  // Create an OpenGL context
  m_glContext = SDL_GL_CreateContext(msgData->GetWindow());
  FATAL_ERRORIF(!m_glContext, std::string("OpenGL Context could not be created ") + SDL_GetError());

  // Initialize GLEW (OpenGL Extension Wrangler)
  glewExperimental = GL_TRUE;
  FATAL_ERRORIF(glewInit(), "GLEW Failed to initialize");

  // Print OpenGL version
  // NONFATAL_ERROR(std::string("OpenGL version: ") + reinterpret_cast<const char*>(glGetString(GL_VERSION)));

  // Set up the viewport
  glViewport(0, 0, 800, 600);

  m_UpdateFxn = &OpenGLDevice::InitializedUpdate;
  return true;
}

/******************************************************************************/
/*!
          Release

\author   John Salguero

\brief    Releases the resources held by the glDevice.


\return   the error code caused by release. 0 is a success
*/
/******************************************************************************/
int OpenGLDevice::Release()
{
  SDL_GL_DeleteContext(m_glContext);
  return 0;
}
