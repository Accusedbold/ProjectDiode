/******************************************************************/
/*!
	All content (C) John Salguero, all rights reserved.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of John Salguero is prohibited.

	\file    OpenGLDevice.h
	\author  John Salguero
	\date    June 23, 2023
	\brief
		This header file declares the OpenGL Device class, which is
		a class that drives the opengl behavior of the game,
		that is - it executes the low level graphics calls
*/
/********************************************************************/
#ifndef _OpenGLDevice
#define _OpenGLDevice

// forward Declaration
class GraphicsSystem;

class OpenGLDevice {

	using UpdateFxn = void (OpenGLDevice::*)(double);

	// called after being initialized
	void InitializedUpdate(double dt);
	// Called when uninitialized
	void DoNothing(double dt);
	// Draws a Renderable to the current buffer
	int DrawRenderable(std::weak_ptr<Renderable> const& renderable);

public:
	// Constructs the device with the graphics system
	OpenGLDevice(std::weak_ptr<GraphicsSystem> const& system);
	// Called to update it every game tick
	void Update(double dt);
	// Used to initialize the device
	bool Initialize
	(std::shared_ptr<WindowCreatedData> const& data, std::shared_ptr<GraphicsSystem> const& system);
	// Used to Release all resources it owns
	int Release();

private:
	// The function used to update the device
	UpdateFxn m_UpdateFxn = &OpenGLDevice::DoNothing;
	// the openGL Context
	SDL_GLContext m_glContext;
	// The Graphics System which holds the resources for rendering
	std::weak_ptr<GraphicsSystem> m_System;
};

#endif