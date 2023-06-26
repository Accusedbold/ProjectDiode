/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Renderable.cpp
  \author  John Salguero
  \date    June 25, 2023
  \brief
    This cpp file declares the Renderable class, which is a
    component that is used in conjunction with the Graphics
    System to draw things to the screen

*/
/********************************************************************/
#include "stdafx.h"

/******************************************************************************/
/*!
          CloneComponent

\author   John Salguero

\brief    Creates a clone of the current component

\return   std::shared_ptr<Component>
          The clone of the component
*/
/******************************************************************************/
std::shared_ptr<Component> Renderable::CloneComponent() const
{
  auto clone = std::static_pointer_cast<Renderable>(ObjectFactory::GetInstance()->CreateComponent(m_Type));

  *clone = *this;

	return clone;
}

ResourceID Renderable::GetModelID() const
{
  return m_Model;
}

bool Renderable::IsTransparent() const
{
  return m_Transparent;
}

glm::vec3 Renderable::GetTransparency() const
{
  return m_Transparency;
}

bool Renderable::IsVisible() const
{
  return m_Visible;
}

bool Renderable::IsDebug() const
{
  return m_Debug;
}

ResourceID Renderable::GetShader(ShaderType type) const
{
  switch (type) {
  case ShaderType::Vertex:
    return m_VShader;
    break;
  case ShaderType::Tesselation:
    return m_TShader;
    break;
  case ShaderType::Geometry:
    return m_GShader;
    break;
  case ShaderType::Fragment:
    return m_FShader;
  default:
    return DEFAULT_FSHADER;
  }
}

void Renderable::SetModel(ResourceID modelID)
{
  m_Model = modelID;
}

void Renderable::SetTransparent(bool transparent)
{
  m_Transparent = transparent;
}

void Renderable::SetTransparency(glm::vec3 const& transparency)
{
  m_Transparency = transparency;
}

void Renderable::SetVisible(bool visible)
{
  m_Visible = visible;
}

void Renderable::SetDebug(bool debug)
{
  m_Debug = debug;
}

void Renderable::SetShader(ShaderType type, ResourceID shader)
{
  switch (type)
  {
  case ShaderType::Vertex:
    m_VShader = shader;
    break;
  case ShaderType::Tesselation:
    m_TShader = shader;
    break;
  case ShaderType::Geometry:
    m_GShader = shader;
    break;
  case ShaderType::Fragment:
    m_FShader = shader;
    break;
  default:
    break;
  }
}
