/******************************************************************/
/*!
	All content (C) John Salguero, all rights reserved.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of John Salguero is prohibited.

	\file    QuaternionTransformation.h
	\author  John Salguero
	\date    June 27, 2023
	\brief
		After looking for a good way to slerp between animation, I did
		not find what I was looking for, so I decided to make this class
		to endable what I wanted I'm pretty proud of myself over this
		simple class
*/
/********************************************************************/
#ifndef QuaternionTransform_H
#define QuaternionTransform_H

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

struct QuaternionTransform {
	// constructor
	QuaternionTransform() = default;
	// copy constructor
	QuaternionTransform(QuaternionTransform const&) = default;
	// Conversion Constructor
	QuaternionTransform(glm::mat4 const&);
	// constructor
	QuaternionTransform(glm::vec3, glm::quat, glm::vec3);
	// Interpolate the transformation
	QuaternionTransform Interpolate(QuaternionTransform const&, float) const;
	// Get the matrix form of the Transform
	glm::mat4 GetTransformation() const;
	// the translation in vec 3 form
	glm::vec3 m_Translate = glm::vec3(0.0f);
	// the rotation that can be slerped
	glm::quat m_Rotate = glm::quat(1.0, 0.0, 0.0, 0.0);
	// the scale in vec3 form
	glm::vec3 m_Scale = glm::vec3(1.0f);
};

#endif