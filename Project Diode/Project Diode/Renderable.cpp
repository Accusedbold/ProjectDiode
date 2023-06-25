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

  clone->m_Parent = m_Parent;
  clone->m_Type = m_Type;
  clone->m_Debug = m_Debug;
  clone->m_ModelName = m_ModelName;
  clone->m_Transparency = m_Transparency;
  clone->m_Transparent = m_Transparent;
  clone->m_Visible = m_Visible;

  // needed for deep copy
  for (int i = 0; i < static_cast<unsigned long long>(ShaderType::Count); ++i) {
    clone->m_Shaders[i] = m_Shaders[i];
  }

	return clone;
}

std::wstring Renderable::GetModelName() const
{
  return m_ModelName;
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

unsigned Renderable::GetShader(ShaderType type) const
{
  return m_Shaders[static_cast<unsigned long long>(type)];
}

void Renderable::SetModel(std::wstring const& modelName)
{
  m_ModelName = modelName;
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

void Renderable::SetShader(ShaderType type, unsigned shader)
{
  m_Shaders[static_cast<unsigned long long>(type)] = shader;
}
