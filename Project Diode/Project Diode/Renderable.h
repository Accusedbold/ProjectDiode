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
  ResourceID GetModelID() const;
  bool IsTransparent() const;
  glm::vec3 GetTransparency() const;
  bool IsVisible() const;
  bool IsDebug() const;
  ResourceID GetShader(ShaderType) const;

  // Setters
  void SetModel(ResourceID);
  void SetTransparent(bool);
  void SetTransparency(glm::vec3 const&);
  void SetVisible(bool);
  void SetDebug(bool);
  void SetShader(ShaderType, ResourceID);
  
private:
  // Resource index of the default model to use
  ResourceID m_Model = 0;

  // whether this model is transparent
  bool m_Transparent = false;

  // Defines how transparent each channel is
  glm::vec3 m_Transparency = glm::vec3(1, 1, 1);

  // whether this is visible
  bool m_Visible = false;

  // whether this is a Debug-Renderable
  bool m_Debug = false;

  // the vertex shader used
  ResourceID m_VShader = DEFAULT_VSHADER;
  // the Tesselation Shader used
  ResourceID m_TShader = DEFAULT_TSHADER;
  // The Geometry Shader used
  ResourceID m_GShader = DEFAULT_GSHADER;
  // The Fragment Shader used
  ResourceID m_FShader = DEFAULT_FSHADER;

};

#endif

