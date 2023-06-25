/******************************************************************/
/*!
	All content (C) John Salguero, all rights reserved.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of John Salguero is prohibited.

	\file    GraphicsSystem.cpp
	\author  John Salguero
	\date    June 23, 2023
	\brief
		This cpp file defines the Graphics System class functions, which is 
		a class that drives the Underlying Graphics of the Game
*/
/********************************************************************/
#include "stdafx.h"
#include "Model.h"
#include "ResourceManager.h"

/******************************************************************************/
/*!
					GraphicsSystem

\author   John Salguero

\brief    Given the Message type and the handler, removes the handler to the map of
					message handlers. This should be used by any handler that is destroyed
					or becomes inaccessable.

\param    name
					The name of the Graphics System
*/
/******************************************************************************/
GraphicsSystem::GraphicsSystem(std::wstring& name) : 
	System(name), m_WindowHandle(nullptr), m_Device(std::weak_ptr<GraphicsSystem>())
{}

/******************************************************************************/
/*!
					Update

\author   John Salguero

\brief    Updates the graphics system, clears the buffer, updates the glDevice,
					and swaps the buffer with the new one.

\param    dt
					The message type to be handled

\return   void
*/
/******************************************************************************/
void GraphicsSystem::Update(double dt)
{
	// Clear the screen
	glClearColor( 1.0f, .5f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	m_Device.Update(dt);

	// Swap buffers
	SDL_GL_SwapWindow(m_WindowHandle);
}

/******************************************************************************/
/*!
					Release

\author   John Salguero

\brief    Releases all resources.

\return   void
*/
/******************************************************************************/
int GraphicsSystem::Release()
{
	// Unregister the listener for WindowCreated Messages
	UnRegisterClassListener(MessageType::WindowCreated, GraphicsSystem, &GraphicsSystem::HandleWindowCreated);

	return m_Device.Release();
}

/******************************************************************************/
/*!
					Initialize

\author   John Salguero

\brief    Initializes the system

\return   void
*/
/******************************************************************************/
void GraphicsSystem::Initialize()
{
	// Register the listener for WindowCreated Messages
	RegisterClassListener(MessageType::WindowCreated, GraphicsSystem, &GraphicsSystem::HandleWindowCreated);
}

/******************************************************************************/
/*!
					GetResource

\author   John Salguero

\brief    Retrieves a resource from the graphics system

\param    type
					The type of the resource

\param    name
					The name of the resource

\return   std::weak_ptr<Resource>
					Pointer to the Resouce
*/
/******************************************************************************/
std::weak_ptr<Resource> GraphicsSystem::GetResource
(ResourceType type, std::wstring const& name)
{
	return m_ResourceManager.GetResource(type, name);
}

/******************************************************************************/
/*!
					LoadResource

\author   John Salguero

\brief    Retrieves a resource from the graphics system

\param    type
					The type of the resource

\param    name
					The name of the resource

\return   std::weak_ptr<Resource>
					Pointer to the Resouce
*/
/******************************************************************************/
ResourceID GraphicsSystem::LoadResource(ResourceType type, std::wstring const& name)
{
	return m_ResourceManager.LoadResource(type, name);
}

/******************************************************************************/
/*!
					HandleWindowCreated

\author   John Salguero

\brief    Handles the event when a window is created by the application.

\param    msg
					The message to be handled

\return   void
*/
/******************************************************************************/
void GraphicsSystem::HandleWindowCreated(std::shared_ptr<Message> const& msg)
{
	auto data = GET_DATA_FROM_MESSAGE(WindowCreatedData, msg);
	m_WindowHandle = data->GetWindow();
	m_Device.Initialize(data, shared_from_this());
}
