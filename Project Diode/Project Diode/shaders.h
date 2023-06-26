/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    shaders.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This header file defines the different Shaders as enums used
    for rendering

*/
/********************************************************************/
#ifndef _Shaders
#define _Shaders

#define DEFAULT_VSHADER 0
#define DEFAULT_TSHADER 2
#define DEFAULT_GSHADER 4
#define DEFAULT_FSHADER 8

using ShaderID = unsigned;

enum class ShaderType : unsigned {
  Vertex,
  Tesselation,
  Geometry,
  Fragment,
  Count
};


#endif
