/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    DestroyedObjectData.cpp
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This cpp file defines the Data for the Object Created Message
    which is used in response to certain actions, which send an event
    when an old object is destroyed that can be handled by systems.
*/
/********************************************************************/
#include "stdafx.h"

/******************************************************************************/
/*!
          DestroyedObjectData

\author   John Salguero

\brief    Constructor to the data object

\param    object
          The object that was deleted
*/
/******************************************************************************/
DestroyedObjectData::DestroyedObjectData(std::shared_ptr<Object> const& object) : m_Object(object)
{}

/******************************************************************************/
/*!
          GetObject

\author   John Salguero

\brief    Returns a pointer to the object

\return   std::weak_ptr<Object>
          A pointer to the object
*/
/******************************************************************************/
std::weak_ptr<Object> DestroyedObjectData::GetObject()
{
  return m_Object;
}
