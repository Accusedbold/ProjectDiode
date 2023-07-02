/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    ResourceTypes.h
  \author  John Salguero
  \date    June 25, 2023
  \brief
    This header file defines the different Resources That the Engine
    Uses

*/
/********************************************************************/
#ifndef ResourceTypes_H
#define ResourceTypes_H

enum class ResourceType {
	Shader,
	Model,
	Texture,
  Material,
	Count
};

#include "Material.h"
#include "Mesh.h"
#include "Model.h"
//#include "Texture.h"

#define SHADER_DIRECTORY L"Resources/Shaders/"
#define MODEL_DIRECTORY L"Resources/Models/"
#define TEXTURE_DIRECTORY L"Resources/Textures/"


#endif