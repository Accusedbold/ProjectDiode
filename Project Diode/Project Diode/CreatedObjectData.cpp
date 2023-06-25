/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    CreatedObjectData.cpp
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This cpp file defines the Data for the Object Created Message
    which is used in response to certain actions, which send an event
    when a new object is created that can be handled by systems.
*/
/********************************************************************/
#include "stdafx.h"

/******************************************************************************/
/*!
          CreatedObjectData

\author   John Salguero

\brief    Constructor to the data object

\param    newObject
          The object that was newly created
*/
/******************************************************************************/
CreatedObjectData::CreatedObjectData(std::weak_ptr<Object> const& newObject) : m_Object(newObject)
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
std::weak_ptr<Object> CreatedObjectData::GetObject()
{
	return m_Object;
}