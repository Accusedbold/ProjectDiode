/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Shader.h
  \author  John Salguero
  \date    June 26, 2023
  \brief
    This header file declares the Shader class, which is a
    resource that contains the shader information OpenGL used to
    process data

*/
/********************************************************************/
#ifndef Shader_H
#define Shader_H

class Shader : public Resource,  public std::enable_shared_from_this<Shader>
{
public:
  // constructor
  Shader(std::wstring const& name, ResourceType type, ResourceID id);

private:
  // The actual code to the shader
  std::string m_Code;
  // The type of Shader it is
  ShaderType m_Type;
  // Id of the Shader
  ShaderID m_ID;
};

#endif

