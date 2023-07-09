/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Renderable.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This header file declares the Renderable class, which is a 
    component that is used in conjunction with the Graphics
    System to draw things to the screen

*/
/********************************************************************/
#ifndef Renderable_H
#define Renderable_H

#include "glm/glm.hpp" // math library

class Renderable : public Component, public std::enable_shared_from_this<Renderable>
{
public:

  // Clones the component
  std::shared_ptr<Component> CloneComponent() const override;
  // Updates the component
  void Update(double dt) override;
  // Releases the component
  void Release() override;
  // Releases the component
  void Initialize() override;

  // Getters
  ResourceID GetModelID() const;
  std::shared_ptr<Model> GetModel() const;
  bool IsTransparent() const;
  float GetTransparency() const;
  bool IsVisible() const;
  bool IsDebug() const;
  bool HasAnimation() const;
  std::set<long> const& GetMaterialFlags();

  // Setters
  void SetModel(ResourceID);
  void SetModel(std::shared_ptr<Model>&);
  void SetIsTransparent(bool);
  void SetTransparency(float);
  void SetVisible(bool);
  void SetDebug(bool);
  
private:
  // Resource index of the model to use
  std::shared_ptr<Model> m_Model;
  // Resource index of the model to use
  std::shared_ptr<Model> m_PrevModel;
  // The different Shaders this renderable uses
  std::set<long> m_MaterialFlags;
  // Whether the model has animation
  bool m_HasAnimation;
  // whether this model is transparent
  bool m_IsTransparent = false;
  // Defines how transparent the renderable is
  float m_TransparencyFactor = 0.0f;
  // whether this is visible
  bool m_Visible = true;
  // whether this is a Debug-Renderable
  bool m_Debug = false;
  // The current animation Time
  float m_CurrTime = 0;
  // The current Frame of the animation animation
  float m_CurrFrame = 0;
  // The next animation Time
  float m_NextAnimTime = 0;
  // The next Frame of the animation animation
  float m_NextAnimFrame = 0;
  // how much between the frames that need to be slurped
  float m_FrameInterpolation = 0;
  // how much between the animations that need to be slurped
  float m_AnimInterpolation = 0;
  // whether the animation is playing
  bool m_isAnimating = false;
  // The current animation
  int m_AnimationID = 0;
  // The next Animation
  int m_nextAnimationID = 0;

};

#endif

