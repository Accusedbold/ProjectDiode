/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Transform.h
  \author  John Salguero
  \date    July 2, 2023
  \brief
    This header file declares the Transform class, which is a class that
    defines the location and orientation of objects

*/
/********************************************************************/
#ifndef Transform_H
#define Transform_H

#include "QuaternionTransform.h"

class Transform : public Component, public std::enable_shared_from_this<Transform> {

public:
  // Clones the component
  std::shared_ptr<Component> CloneComponent() const override;
  // updates the component
  void Update(double) override;
  // Releases the component
  void Release() override;
  // Initializes the component
  void Initialize() override;
  // Rotate using a quaternion
  void Rotate(glm::quat const& rotation);
  // Translate the transform using a vector
  void Translate(glm::vec3 const&);
  // Scale using a vector
  void Scale(glm::vec3 const&);
  // Get the Postion
  glm::vec3 const& GetPosition() const;
  // Get the rotation
  glm::quat const& GetRotation() const;
  // Get the Scale
  glm::vec3 const& GetScale() const;
  // Get world Transformation Matrix
  glm::mat4 GetWorldMatrix() const;
  // Get World transformation QuaternionTransform
  QuaternionTransform const& GetWorldTransform() const;
  // Set the world position
  void SetPosition(glm::vec3 const&);
  // Set the Rotation
  void SetRotation(glm::quat const&);
  // Set the scale
  void SetScale(glm::vec3 const&);
private:
  // The Scale, Location, and Rotation of the object
  QuaternionTransform m_Transform;
};

#endif