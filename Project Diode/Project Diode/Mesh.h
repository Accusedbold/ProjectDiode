/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Mesh.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This header file declares the Mesh class, which is a
    resource that contains everything needed to draw by 
    the OpenGL Device

*/
/********************************************************************/
#ifndef _Mesh
#define _Mesh

class Mesh {
public:

private:

  std::wstring m_Name;
  std::vector<std::wstring> m_Textures;
  std::vector<std::wstring> m_Shaders;
  glm::vec4 m_Color;
};

#endif