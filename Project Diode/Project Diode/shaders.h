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

enum class ShaderType : unsigned long long {
  Vertex,
  Tesselation,
  Geometry,
  Fragment,
  Count
};

enum class VertexShaders : unsigned long long {
  Default = 0,
};

enum class TessellationShaders : unsigned long long {
  Default = 2,
};

enum class GeometryShaders : unsigned long long {
  Default = 4,
};

enum class FragmentShaders : unsigned long long {
  Default = 8,
};


#endif
