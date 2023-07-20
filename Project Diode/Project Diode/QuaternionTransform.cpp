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
	retVal.m_Scale = m_Scale *(1 - delta)+rhs.m_Scale * (delta);
	retVal.m_Rotate = glm::slerp(m_Rotate, rhs.m_Rotate, delta);
	retVal.m_Translate = m_Translate *(1 - delta)+rhs.m_Translate * (delta);
	return retVal;
}

glm::mat4 QuaternionTransform::GetTransformation() const
{
	glm::mat4 retVal = glm::scale(glm::toMat4(m_Rotate), m_Scale);
	retVal[3][0] = m_Translate[0];
	retVal[3][1] = m_Translate[1];
	retVal[3][2] = m_Translate[2];
	return retVal;
}
