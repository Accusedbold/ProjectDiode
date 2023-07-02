/******************************************************************/
/*!
	All content (C) John Salguero, all rights reserved.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of John Salguero is prohibited.

	\file    QuaternionTransformation.cpp
	\author  John Salguero
	\date    June 27, 2023
	\brief
		After looking for a good way to slerp between animation, I did
		not find what I was looking for, so I decided to make this class
		to endable what I wanted I'm pretty proud of myself over this
		simple class
*/
/********************************************************************/
#include "stdafx.h"
#include "QuaternionTransform.h"

QuaternionTransform::QuaternionTransform(glm::vec3 trans, glm::quat rot, glm::vec3 scale)
{
	m_Translate = trans;
	m_Rotate = rot;
	m_Scale = scale;
}

QuaternionTransform QuaternionTransform::Interpolate(QuaternionTransform const& rhs, float delta) const
{
	QuaternionTransform retVal = QuaternionTransform();
	retVal.m_Scale = m_Scale * (delta) + rhs.m_Scale * (1 - delta);
	retVal.m_Rotate = glm::slerp(m_Rotate, rhs.m_Rotate, delta);
	retVal.m_Translate = m_Translate * (delta) + rhs.m_Translate * (1 - delta);
	return retVal;
}
