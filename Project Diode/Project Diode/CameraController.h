/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    CameraController.h
  \author  John Salguero
  \date    July 11, 2023
  \brief
    This header file declares the CameraController class, which is a class that
    defines the behavior of controller objects. This Component allows the
    player to control the camera of the object

*/
/********************************************************************/
#ifndef CameraController_H
#define CameraController_H

class CameraController : public Component, public std::enable_shared_from_this<CameraController> {

public:
  // Clones the component
  virtual std::shared_ptr<Component> CloneComponent() const;
  // updates the component
  virtual void Update(double);
  // Releases the component
  virtual void Release();
  // Initializes the component
  virtual void Initialize();
private:
  // Handles Input messages
  void HandleInputMessage(std::shared_ptr<Message> const& msg);
  // Camera of the object being controlled
  std::weak_ptr<Camera> m_Camera;
  // Transform of the object being controlled
  std::weak_ptr<Transform> m_Transform;
};

#endif