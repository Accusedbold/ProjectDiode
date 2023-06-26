/******************************************************************/
/*!
	All content (C) John Salguero, all rights reserved.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of John Salguero is prohibited.

	\file    Model.cpp
	\author  John Salguero
	\date    June 25, 2023
	\brief
		This cpp file defines the Model member functions, which manipulates
		the object that has  meshes, which are objects that contain everything 
		OpenGL needs to draw to the screen
*/
/********************************************************************/
#include "stdafx.h"
#include "Mesh.h"	 // Mesh
#include "Model.h" // Model

/******************************************************************************/
/*!
					Model

\author   John Salguero

\brief    Constructor to the Model Resource

\param    name
					The name of the Resource

\param    type
					The type of the Resource

\param    id
					The id of the Resource
*/
/******************************************************************************/
Model::Model(std::wstring const& name, ResourceType type, ResourceID id) : Resource(name, type, id)
{
}
