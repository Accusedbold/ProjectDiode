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
#include <glm/gtx/matrix_decompose.hpp>

QuaternionTransform::QuaternionTransform(glm::mat4 const& transformation)
{
	glm::vec3 skew;
	glm::vec4 perspective;

	glm::decompose(transformation, m_Scale, m_Rotate, m_Translate, skew, perspective);
}

QuaternionTransform::QuaternionTransform(glm::vec3 trans, glm::quat rot, glm::vec3 scale)
{
	m_Translate = trans;
	m_Rotate = rot;
	m_Scale = scale;
}

QuaternionTransform QuaternionTransform::Interpolate(QuaternionTransform const& rhs, float delta) const
{
	QuaternionTransform retVal = QuaternionTransform();
	retVal.m_Scale = m_Scale *(delta)+rhs.m_Scale * (1 - delta);
	retVal.m_Rotate = glm::slerp(m_Rotate, rhs.m_Rotate, 1 - delta);
	retVal.m_Translate = m_Translate *(delta)+rhs.m_Translate * (1 - delta);
	return retVal;
}

glm::mat4 QuaternionTransform::GetTransformation() const
{
	auto scale = glm::scale(glm::mat4(1.0f), m_Scale);
	auto rotate = glm::toMat4(m_Rotate);
	auto translate = glm::translate(glm::mat4(1.0f), m_Translate);
	return translate * rotate * scale;
}
