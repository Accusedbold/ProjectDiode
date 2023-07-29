/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Texture.h
  \author  John Salguero
  \date    July 1, 2023
  \brief
    This header file declares the Model class, which is a
    resource that contains meshes that are drawn by OpenGL

*/
/********************************************************************/
#ifndef Texture_H
#define Texture_H

struct Texture : public Resource, public std::enable_shared_from_this<Texture>
{
  Texture(std::wstring const& name, ResourceID id, ResourceType const& type = ResourceType::Texture);

  GLuint m_textureID = 0;
};

#endif