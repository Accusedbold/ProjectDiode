/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Message.cpp
  \author  John Salguero
  \date    June 21, 2023
  \brief
    This cpp file defines the Message Class, which is used in response to certain
    actions, which send an event that can be handled
*/
/********************************************************************/
#include "stdafx.h"

/******************************************************************************/
/*!
            Message

\author     John Salguero

\brief      Constructs the Message class

\param      system
            The label that states where the message originates from

\param      id
            The type of message it is

\param      data
            The data that the message carries, if it needs
*/
/******************************************************************************/
Message::Message(std::wstring const& system, MessageType id, std::shared_ptr<void> const& data) : m_MessageType(id), m_FromSystem(system), m_Data(data)
{}

/******************************************************************************/
/*!
            GetMessageType

\author     John Salguero

\brief      returns the message type

\return     MessageType
            Ultimately how the message is handled
*/
/******************************************************************************/
MessageType Message::GetMessageType() const 
{ 
	return m_MessageType; 
}

/******************************************************************************/
/*!
            GetOriginatingSystem

\author     John Salguero

\brief      Returns where the message came from

\return     wstring
            The label the message came from
*/
/******************************************************************************/
const std::wstring Message::GetOriginatingSystem() const
{
	return m_FromSystem;
}

/******************************************************************************/
/*!
            GetData

\author     John Salguero

\brief      Returns the pointer to the data that pertains to the message

\return     void*
            The data that the message holds
*/
/******************************************************************************/
const std::shared_ptr<void> Message::GetData() const
{
	return m_Data;
}
