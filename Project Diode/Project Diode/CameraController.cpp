/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    CameraController.cpp
  \author  John Salguero
  \date    July 11, 2023
  \brief
    This cpp file defines the CameraController class, which is a class that
    defines the behavior of controller objects. This Component allows the
    player to control the camera of the object

*/
/********************************************************************/
#include "stdafx.h"

std::shared_ptr<Component> CameraController::CloneComponent() const
{
  auto clone = std::static_pointer_cast<CameraController>(ObjectFactory::GetInstance()->CreateComponent(m_Type));

  *clone = *this;

  return clone;
}

void CameraController::Update(double)
{
}

void CameraController::Release()
{
  UnRegisterClassListener(MessageType::Input, CameraController, &CameraController::HandleInputMessage);
}

void CameraController::Initialize()
{
  RegisterClassListener(MessageType::Input, CameraController, &CameraController::HandleInputMessage);
  m_Camera = m_Parent.lock()->has(Camera);
  m_Transform = m_Parent.lock()->has(Transform);
}

void CameraController::HandleInputMessage(std::shared_ptr<Message> const& msg)
{
  if (m_Camera.expired())
    return;
  auto &data = *GET_DATA_FROM_MESSAGE(SDL_Event, msg);
  auto& camera = *m_Camera.lock();
  glm::vec3 position;
  if (!m_Transform.expired())
    position = m_Transform.lock()->GetPosition();

  switch (data.type)
  {
  case SDL_KEYDOWN:
    switch (data.key.keysym.sym)
    {
    case SDLK_w:
      if (!m_Transform.expired())
        m_Transform.lock()->SetPosition(position + glm::vec3(camera.GetLookAt()));
      break;
    case SDLK_a:
      if (!m_Transform.expired())
        m_Transform.lock()->SetPosition(position - glm::vec3(camera.GetStrafeVector()));
      break;
    case SDLK_s:
      if (!m_Transform.expired())
        m_Transform.lock()->SetPosition(position - glm::vec3(camera.GetLookAt()));
      break;
    case SDLK_d:
      if (!m_Transform.expired())
        m_Transform.lock()->SetPosition(position + glm::vec3(camera.GetStrafeVector()));
      break;
    case SDLK_e:
      if (!m_Transform.expired())
        m_Transform.lock()->SetPosition(position + glm::vec3(0.0f, 1.0f, 0.0f));
      break;
    case SDLK_q:
      if (!m_Transform.expired())
        m_Transform.lock()->SetPosition(position - glm::vec3(0.0f, 1.0f, 0.0f));
      break;
    case SDLK_c:
      if (!m_Transform.expired())
        camera.SetLookAt({ -m_Transform.lock()->GetPosition(), 0.0f});
      break;
    default:
      break;
    }
    break;
  case SDL_MOUSEMOTION:
  {
    float degsX = static_cast<float>(data.motion.xrel) / -1000, degsY = static_cast<float>(data.motion.yrel) / -1000;
    camera.TurnFPCam(degsX);
    camera.LiftFPCam(degsY);
    break;
  }
  default:
    break;
  }
}
