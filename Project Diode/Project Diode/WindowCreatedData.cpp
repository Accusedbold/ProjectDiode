/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    WindowCreatedData.cpp
  \author  John Salguero
  \date    June 23, 2023
  \brief
    This cpp file defines the Data for the Window Created Message
    which is used in response to certain actions, which send an event
    when a new window is created that can be handled by systems such
    as graphics
*/
/********************************************************************/
#include "stdafx.h"

/******************************************************************************/
/*!
            WindowCreatedData

\author     John Salguero

\brief      Constructor to the object

\param      window
            The window handle

\param      width
            width of the window

\param      height
            height of the window
*/
/******************************************************************************/
WindowCreatedData::WindowCreatedData(SDL_Window* window, int width, int height) : m_Window(window), m_Width(width), m_Height(height)
{
}

/******************************************************************************/
/*!
            GetWindow

\author     John Salguero

\brief      Gets the window handle from the data object

\return     The Window Handle that SDL created
*/
/******************************************************************************/
SDL_Window* WindowCreatedData::GetWindow() const
{
	return m_Window;
}

/******************************************************************************/
/*!
            GetWidth

\author     John Salguero

\brief      Gets the width of the window

\return     The width of the window
*/
/******************************************************************************/
int WindowCreatedData::GetWidth() const
{
	return m_Height;
}

/******************************************************************************/
/*!
            GetHeight

\author     John Salguero

\brief      Gets the height of the window

\return     The height of the window
*/
/******************************************************************************/
int WindowCreatedData::GetHeight() const
{
	return m_Width;
}


