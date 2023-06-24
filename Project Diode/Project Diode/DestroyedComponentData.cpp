/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    DestroyedComponentData.cpp
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This cpp file defines the Data for the Object Created Message
    which is used in response to certain actions, which send an event
    when an old component is destroyed that can be handled by systems.
*/
/********************************************************************/
#include "stdafx.h"

/******************************************************************************/
/*!
          DestroyedComponentData

\author   John Salguero

\brief    Constructor to the data object

\param    object
          The component that was deleted
*/
/******************************************************************************/
DestroyedComponentData::DestroyedComponentData(std::shared_ptr<Component> const& object) : m_Component(object)
{}

/******************************************************************************/
/*!
          GetComponent

\author   John Salguero

\brief    Returns a pointer to the component

\return   std::weak_ptr<Component>
          A pointer to the component
*/
/******************************************************************************/
std::weak_ptr<Component> DestroyedComponentData::GetComponent()
{
  return m_Component;
}
