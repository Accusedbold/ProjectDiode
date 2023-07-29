/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Camera.cpp
  \author  John Salguero
  \date    July 3, 2023
  \brief
    This cpp file declares the Camera class, which is a class that
    defines the behavior of the camera that is used to project images
    into camera space

*/
/********************************************************************/
#include "stdafx.h"
#include "Texture.h"

std::shared_ptr<Component> Camera::CloneComponent() const
{
	auto clone = std::static_pointer_cast<Camera>(ObjectFactory::GetInstance()->CreateComponent(m_Type));

	*clone = *this;

	return clone;
}

void Camera::Update(double)
{
}

void Camera::Release()
{
  UnRegisterClassListener(MessageType::WindowResized, Camera, &Camera::HandleResizeWindow);
}

void Camera::Initialize()
{
  RegisterClassListener(MessageType::WindowResized, Camera, &Camera::HandleResizeWindow);
}

/* Get The Camera Matrix in Row-Major Order */
glm::mat4 Camera::GetInverseOrthogonalTransformation()
{
	glm::mat4 retVal(m_Right, m_Up, -m_LookAt, glm::vec4(0, 0, 0, 1));
	return glm::transpose(retVal);
}


/* Get The Camera Matrix in Row-Major Order */
glm::mat4 Camera::GetInverseTranslationalTransformation()
{
  glm::mat4 retVal(1.0f);
  std::shared_ptr<Transform> spTransform = m_Parent.lock()->has(Transform).lock();

  if (spTransform)
  {
    retVal = glm::translate(retVal , -spTransform->GetPosition());
  }

  return retVal;
}


/* Get The Camera Matrix in Row-Major Order */
glm::mat4 Camera::GetCameraTransformation()
{
  return GetInverseOrthogonalTransformation() * GetInverseTranslationalTransformation();
}

/* Get The Camera Width */
unsigned Camera::GetCameraWidth()
{
  return m_Width;
}

/* Get The Camera Height */
unsigned Camera::GetCameraHeight()
{
  return m_Height;
}

/* Get The Camera Field of View in radians */
float Camera::GetCameraFOV()
{
  return m_FOV;
}

/* Get The Camera Far */
float Camera::GetCameraFar()
{
  return m_Far;
}

/* Get The Camera Near */
float Camera::GetCameraNear()
{
  return m_Near;
}

bool Camera::GetDidChange()
{
  return m_WidthHeightChanged;
}

/* Retrieves the Skymap ID */
GLint Camera::GetSkyMapID()
{
  return m_SkyMap->m_textureID;
}

/* Get The Camera Right Vector (very useful for game logic) */
const glm::vec4& Camera::GetRightVector(void)
{
  return m_Right;
}

/* Get The Camera LookAt Vector */
const glm::vec4& Camera::GetLookAt(void)
{
  return m_LookAt;
}

/* Get The Camera Up Vector */
const glm::vec4& Camera::GetUpVector() const
{
  return m_Up;
}

/* Set the look at, and keep proper perspective - Camera is oriented fps style */
void Camera::SetLookAt(glm::vec4 const& look)
{
  m_LookAt = glm::normalize(look);

  m_Right = glm::vec4(glm::normalize(glm::cross(glm::vec3(m_LookAt), glm::vec3(0.0f, 1.0f, 0.0f))), 0.0f);
  m_Up = glm::vec4(glm::normalize(glm::cross(glm::vec3(m_Right), glm::vec3(m_LookAt))), 0.0f);
}

/* Set The Camera Width */
void Camera::SetCameraWidth(unsigned width)
{
  m_Width = width;
  m_WidthHeightChanged = true;
}

/* Set The Camera Height */
void Camera::SetCameraHeight(unsigned height)
{
  m_Height = height;
  m_WidthHeightChanged = true;
}

/* Set The Camera Field of View in radians */
void Camera::SetCameraFOV(float rads)
{
  m_FOV = rads;
}

/* Set The Camera Far */
void Camera::SetCameraFar(float farf)
{
  m_Far = farf;
}

/* Set The Camera Near */
void Camera::SetCameraNear(float nearf)
{
  m_Near = nearf;
}

/* Set The Camera change bool */
void Camera::SetDidChange(bool didChange)
{
  m_WidthHeightChanged = didChange;
}

/* Turn the Camera left/right +/- */
void Camera::RotateYaw(float degs)
{
  glm::mat4 rotate(1.0f);
  glm::vec3 up(m_Up);
  rotate = glm::rotate(rotate, degs, up);

  m_LookAt = rotate * m_LookAt;
  m_Right = rotate * m_Right;
}

/* Lift the camera up/down +/- */
void Camera::RotatePitch(float degs)
{
  glm::mat4 rotate(1.0f);
  glm::vec3 right(m_Right);
  rotate = glm::rotate(rotate, degs, right);

  m_LookAt = rotate * m_LookAt;
  m_Up = rotate * m_Up;
}

/* Roll the camera +/- */
void Camera::RotateRoll(float degs)
{
  glm::mat4 rotate(1.0f);
  glm::vec3 look(m_LookAt);
  rotate = glm::rotate(rotate, degs, look);

  m_Right = rotate * m_Right;
  m_Up = rotate * m_Up;
}

/* Turn cam left/right +/- */
void Camera::TurnFPCam(float degs)
{
  glm::mat4 rotate(1.0f);
  rotate = glm::rotate(rotate, degs, glm::vec3(0.0f, 1.0f, 0.0));

  m_Right = rotate * m_Right;
  m_Up = rotate * m_Up;

  m_LookAt = glm::vec4(glm::normalize(glm::cross(glm::vec3(m_Up), glm::vec3(m_Right))), 0.0f);
}

/* Turn cam up/down +/- */
void Camera::LiftFPCam(float degs)
{
  glm::mat4 rotate(1.0f);
  rotate = glm::rotate(rotate, degs, glm::vec3(m_Right));

  m_Up = rotate * m_Up;
  if (m_Up.y < 0)
  {
    m_Up.y = 0;
    m_Up = glm::normalize(m_Up);
  }

  m_LookAt = glm::vec4(glm::normalize(glm::cross(glm::vec3(m_Up), glm::vec3(m_Right))), 0.0f);
}

/* Get the first person forward vector with ground plane being x axis */
glm::vec4 Camera::GetForwardVector()
{
  glm::vec4 retVal{ m_LookAt.x, 0.0f, m_LookAt.z, 0.0f };
  if (glm::dot(retVal, retVal) != 0)
    retVal = glm::normalize(retVal);
  else if (m_LookAt.y < 0)
    retVal = m_Up;
  else
    retVal = -m_Up;

  return retVal;
}

/* Get the first person Strafe vector with ground plane being x axis */
glm::vec4 Camera::GetStrafeVector()
{
  glm::vec4 retVal{ m_Right.x, 0.0f, m_Right.z, 0.0f };
  retVal = normalize(retVal);

  return retVal;
}

/* Get the Perspective Projectsion of the camera */
glm::mat4 Camera::GetPerpectiveMatrix() {
  return glm::perspectiveFov(m_FOV, static_cast<float>(m_Width), static_cast<float>(m_Height), m_Near, m_Far);
}

/* Get the draw list of collidable Renderables */
std::vector<std::weak_ptr<Renderable>>& Camera::GetDrawList()
{
  return m_RenderablesWithinFrustum;
}

/* Whether the camera has a skymap */
bool Camera::HasSkyMap()
{
  return m_SkyMap.get();
}

/* Sets the textures for a skymap */
void Camera::SetSkyMap(std::shared_ptr<Texture> const& skymap)
{
  m_SkyMap = skymap;
}

/* Handles when the window gets resized */
void Camera::HandleResizeWindow(std::shared_ptr<Message> const& msg)
{
  auto data = GET_DATA_FROM_MESSAGE(SDL_WindowEvent, msg);
  SDL_GL_GetDrawableSize(SDL_GetWindowFromID(data->windowID), &m_Width, &m_Height);
}
