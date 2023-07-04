/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Collider.cpp
  \author  John Salguero
  \date    July 4, 2023
  \brief
    This header file declares the Collider class, which is a class that
    allows for colision detection.

*/
/********************************************************************/
#include "stdafx.h"

std::shared_ptr<Component> Collider::CloneComponent() const
{
	auto clone = std::static_pointer_cast<Collider>(ObjectFactory::GetInstance()->CreateComponent(m_Type));

	*clone = *this;

	return clone;
}

void Collider::Update(double)
{
}

void Collider::Release()
{
}

void Collider::Initialize()
{
}
