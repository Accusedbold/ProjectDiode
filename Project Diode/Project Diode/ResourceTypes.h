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
	Model,
	Texture,
  Material,
  CubeMap,
	Count
};

#include "Material.h"
#include "Mesh.h"
#include "Model.h"
//#include "Texture.h"

#define SHADER_DIRECTORY L"Resources/Shaders/"
#define MODEL_DIRECTORY L"Resources/Models/"
#define TEXTURE_DIRECTORY L"Resources/Textures/"
#define POS_X_FILENAME L"posx.png"
#define NEG_X_FILENAME L"negx.png"
#define POS_Y_FILENAME L"posy.png"
#define NEG_Y_FILENAME L"negy.png"
#define POS_Z_FILENAME L"posz.png"
#define NEG_Z_FILENAME L"negz.png"


#endif