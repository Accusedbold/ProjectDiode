/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Shader.cpp
  \author  John Salguero
  \date    June 26, 2023
  \brief
    This cpp file defines the Shader class member functions, which 
    manipulate the shaders, which are used to program the GPU which
    process the objects drawn to the buffer
*/
/********************************************************************/
#include "stdafx.h"

/******************************************************************************/
/*!
          Shader

\author   John Salguero

\brief    Constructor to the Shader Resource

\param    name
          The name of the Resource

\param    type
          The type of the Resource

\param    id
          The id of the Resource
*/
/******************************************************************************/
Shader::Shader(std::wstring const& name, ResourceType type, ResourceID id) : Resource(name, type, id)
{}
