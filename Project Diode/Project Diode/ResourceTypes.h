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
#ifndef _ResourceTypes
#define _ResourceTypes

#define SHADER_DIRECTORY "Resources/Shaders"
#define MODEL_DIRECTORY "Resources/Models"
#define TEXTURE_DIRECTORY "Resources/Textures"

enum class ResourceType {
	Shader,
	Model,
	Texture,
	Count
};

#endif