/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Transform.cpp
  \author  John Salguero
  \date    July 2, 2023
  \brief
    This cpp file declares the Transform class, which is a class that
    defines the location and orientation of objects

*/
/********************************************************************/
#include "stdafx.h"

std::shared_ptr<Component> Transform::CloneComponent() const
{
  auto clone = std::static_pointer_cast<Transform>(ObjectFactory::GetInstance()->CreateComponent(m_Type));

  *clone = *this;

  return clone;
}

void Transform::Update(double)
{
}

void Transform::Release()
{
}

void Transform::Initialize()
{
}

void Transform::Rotate(glm::quat const& rotation)
{
  m_Transform.m_Rotate *= rotation;
}

void Transform::Translate(glm::vec3 const& translation)
{
  m_Transform.m_Translate += translation;
}

void Transform::Scale(glm::vec3 const& scale)
{
  m_Transform.m_Scale *= scale;
}

glm::vec3 const& Transform::GetPosition() const
{
  return m_Transform.m_Translate;
}

glm::quat const& Transform::GetRotation() const
{
  return m_Transform.m_Rotate;
}

glm::vec3 const& Transform::GetScale() const
{
  return m_Transform.m_Scale;
}

glm::mat4 Transform::GetWorldMatrix() const
{
  auto rotate = glm::mat4_cast(m_Transform.m_Rotate);
  return glm::translate(rotate * glm::scale(glm::mat4(1.0f), m_Transform.m_Scale), m_Transform.m_Translate);
}

QuaternionTransform const& Transform::GetWorldTransform() const
{
  return m_Transform;
}

void Transform::SetPosition(glm::vec3 const& pos)
{
  m_Transform.m_Translate = pos;
}

void Transform::SetRotation(glm::quat const& rotate)
{
  m_Transform.m_Rotate = rotate;
}

void Transform::SetScale(glm::vec3 const& scale)
{
  m_Transform.m_Scale = scale;
}
