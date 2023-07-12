/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Camera.h
  \author  John Salguero
  \date    July 3, 2023
  \brief
    This header file declares the Camera class, which is a class that
    defines the behavior of the camera that is used to project images
    into camera space

*/
/********************************************************************/
#ifndef Camera_H
#define Camera_H

class Camera : public Component, public std::enable_shared_from_this<Camera> {

public:
  // Clones the component
  std::shared_ptr<Component> CloneComponent() const override;
  // updates the component
  void Update(double) override;
  // Releases the component
  void Release() override;
  // Initializes the component
  void Initialize() override;

  // Get The Camera Matrix in Row-Major Order 
  glm::mat4 GetInverseOrthogonalTransformation();

  // Get The Camera Matrix in Row-Major Order 
  glm::mat4 GetInverseTranslationalTransformation();

  // Get The Camera Matrix in Row-Major Order 
  glm::mat4 GetCameraTransformation();

  // Get The Projection Matrix
  glm::mat4 GetPerpectiveMatrix();

  // Get The Camera Width 
  unsigned GetCameraWidth();

  // Get The Camera Height 
  unsigned GetCameraHeight();

  // Get The Camera Field of View in radians 
  float GetCameraFOV();

  // Get The Camera Far 
  float GetCameraFar();

  // Get The Camera Near 
  float GetCameraNear();

  // Whether or not the width or height changed 
  bool GetDidChange();

  // Get The Right Vector 
  const glm::vec4& GetRightVector(void);

  // Get The LookAt Vector 
  const glm::vec4& GetLookAt(void);

  // Get The Up Vector 
  const glm::vec4& GetUpVector() const;

  // Set The Camera Width 
  void SetLookAt(glm::vec4 const&);

  // Set The Camera Width 
  void SetCameraWidth(unsigned);

  // Set The Camera Height 
  void SetCameraHeight(unsigned);

  // Set The Camera Field of View in radians 
  void SetCameraFOV(float rads);

  // Set The Camera Far 
  void SetCameraFar(float farf);

  // Set The Camera Near 
  void SetCameraNear(float nearf);

  // Set The Camera change bool 
  void SetDidChange(bool didChange);

  // Turn the Camera left/right +/- 
  void RotateYaw(float degs);

  // Lift the camera up/down +/- 
  void RotatePitch(float degs);

  // Roll the camera +/- 
  void RotateRoll(float degs);

  // Turn first person cam left/right +/- 
  void TurnFPCam(float degs);

  // Turn first person cam up/down +/- 
  void LiftFPCam(float degs);

  // Get the first person forward vector with ground plane being x axis 
  glm::vec4 GetForwardVector();

  // Get the first person forward vector with ground plane being x axis 
  glm::vec4 GetStrafeVector();

  // Gets a vector of renderables the camera needs to draw
  std::vector<std::weak_ptr<Renderable>>& GetDrawList();

private:
  // used to construct the inverse orthogonal matrix
  glm::vec4 m_LookAt = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
  glm::vec4 m_Right = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);;
  glm::vec4 m_Up = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);;

  // Used for projection
  unsigned m_Width = 800;
  unsigned m_Height = 600;
  float m_FOV = 170.0f;
  float m_Near = 2.5f;
  float m_Far = 10'000.0f;

  // used to resize buffers
  bool m_WidthHeightChanged;

  // Objects to draw
  std::vector<std::weak_ptr<Renderable>> m_RenderablesWithinFrustum;
};

#endif