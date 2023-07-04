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
#include "QuaternionTransform.h" // QuaternionTransform
#include "Joint.h"               // Joint
#include "Animation.h"           // Animation
#include "Mesh.h"	               // Mesh
#include "Model.h"               // Model
#include "Material.h"            // Material
#include "ResourceManager.h"     // ResourceManager 

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
	UnRegisterClassListener(MessageType::ComponentCreated, GraphicsSystem, &GraphicsSystem::HandleComponentCreated);
	UnRegisterClassListener(MessageType::ComponentDestroyed, GraphicsSystem, &GraphicsSystem::HandleComponentDestroyed);

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
	RegisterClassListener(MessageType::ComponentCreated, GraphicsSystem, &GraphicsSystem::HandleComponentCreated);
	RegisterClassListener(MessageType::ComponentDestroyed, GraphicsSystem, &GraphicsSystem::HandleComponentDestroyed);
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

/******************************************************************************/
/*!
					HandleComponentCreated

\author   John Salguero

\brief    Handles the event when a Component is created to add colliderless
					renderables to the collection

\param    msg
					The message to be handled

\return   void
*/
/******************************************************************************/
void GraphicsSystem::HandleComponentCreated(std::shared_ptr<Message> const& msg)
{
	auto component = GET_DATA_FROM_MESSAGE(Component, msg);
	auto parent = component->GetParent().lock();
	if (component->GetType() == ComponentType::Renderable)
	{
		auto collider = parent->has(Collider);
		if (collider.expired())
			m_ColliderlessRenderables.push_back(std::static_pointer_cast<Renderable>(component));
	}

	switch (component->GetType()) {
		case ComponentType::Collider:
		{
			auto renderable = parent->has(Renderable);
			if (!renderable.expired())
			{
				for (auto it = m_ColliderlessRenderables.begin(), end = m_ColliderlessRenderables.end();
					it != end; ++it)
				{
					if (it->lock() == renderable.lock())
					{
						m_ColliderlessRenderables.erase(it);
						break;
					}
				}
			}
			break;
		}
		case ComponentType::Camera:
		{
			WARN("Needs to check for Teleportals when implemented");
			m_Cameras.push_back(std::static_pointer_cast<Camera>(component));
			break;
		}
		default:
			break;
	}
}

/******************************************************************************/
/*!
					HandleComponentDestroyed

\author   John Salguero

\brief    Handles the event when a Component is destroyed to remove colliderless
					renderables from the collection

\param    msg
					The message to be handled

\return   void
*/
/******************************************************************************/
void GraphicsSystem::HandleComponentDestroyed(std::shared_ptr<Message> const& msg)
{
	// Get the component from the message
	auto component = GET_DATA_FROM_MESSAGE(Component, msg);
	auto parent = component->GetParent().lock();

	switch (component->GetType())
	{
		case ComponentType::Renderable:
			for (auto it = m_ColliderlessRenderables.begin(), end = m_ColliderlessRenderables.end();
				it != end; ++it)
			{
				if (it->lock() == component)
				{
					m_ColliderlessRenderables.erase(it);
					break;
				}
			}
			break;
		case ComponentType::Camera:
			for (auto it = m_Cameras.begin(), end = m_Cameras.end(); it != end; ++it) 
			{
				if (it->lock() == component)
				{
					m_Cameras.erase(it);
					break;
				}
			}
			break;
		default:
			WARN("Needs to check for Teleportals when implemented");
	}

}

/******************************************************************************/
/*!
					DrawCameras

\author   John Salguero

\brief    Draws all the cameras not associated with a teleportal

\return   void
*/
/******************************************************************************/
void GraphicsSystem::DrawCameras()
{
	for (auto const& camera : m_Cameras)
	{
		std::vector<std::weak_ptr<Renderable>> drawList;
		drawList.swap(camera.lock()->GetDrawList());
		drawList.insert(drawList.end(), m_ColliderlessRenderables.begin(), m_ColliderlessRenderables.end());

	}
}
