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
#ifndef _Renderable
#define _Renderable

#include "glm/glm.hpp" // math library

class Renderable : public Component, public std::enable_shared_from_this<Renderable>
{
public:

  // Clones the component
  std::shared_ptr<Component> CloneComponent() const override;

  // Getters
  std::wstring GetModelName() const;
  bool IsTransparent() const;
  glm::vec3 GetTransparency() const;
  bool IsVisible() const;
  bool IsDebug() const;
  unsigned GetShader(ShaderType) const;

  // Setters
  void SetModel(std::wstring const&);
  void SetTransparent(bool);
  void SetTransparency(glm::vec3 const&);
  void SetVisible(bool);
  void SetDebug(bool);
  void SetShader(ShaderType, unsigned);
  
private:
  // Name of the model to use
  std::wstring m_ModelName = L"default";

  // whether this model is transparent
  bool m_Transparent = false;

  // Defines how transparent each channel is
  glm::vec3 m_Transparency = glm::vec3(1, 1, 1);

  // whether this is visible
  bool m_Visible = false;

  // whether this is a Debug-Renderable
  bool m_Debug = false;

  // Shaders to use
  unsigned m_Shaders[static_cast<unsigned long long>(ShaderType::Count)] = {};

};

#endif

