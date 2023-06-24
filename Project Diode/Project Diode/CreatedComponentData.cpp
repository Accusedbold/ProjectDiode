/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    CreatedComponent.cpp
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This cpp file defines the member functions for the Component Created
    Message Data Class which is used in response to component creatioin, 
    which send an event holding that data
*/
/********************************************************************/
#include "stdafx.h"

/******************************************************************************/
/*!
          CreatedComponentData

\author   John Salguero

\brief    Constructor, initializes the member variables

\param    newComponent
          weak pointer to the component created

\param    componentType
          Type of the component created

\return   void
*/
/******************************************************************************/
CreatedComponentData::CreatedComponentData(std::weak_ptr<Component> const& newComponent, ComponentType componentType) : m_Component(newComponent), m_Type(componentType)
{
}

/******************************************************************************/
/*!
          GetComponent

\author   John Salguero

\brief    The component created

\return   weak_ptr<Component>
          Weak pointer to the component created
*/
/******************************************************************************/
std::weak_ptr<Component> CreatedComponentData::GetComponent()
{
	return std::weak_ptr<Component>();
}

/******************************************************************************/
/*!
          GetType

\author   John Salguero

\brief    The Type of the component created

\return   ComponentType
          The Type of the component created

*/
/******************************************************************************/
ComponentType CreatedComponentData::GetType()
{
	return ComponentType();
}
