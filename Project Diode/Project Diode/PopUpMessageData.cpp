/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    PopUpMessageData.cpp
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This cpp file is used to declare the data class for the
    Popup Message Class used to communicate a message
*/
/********************************************************************/

#include "stdafx.h"

/******************************************************************************/
/*!
            ErrorMessage

\author     John Salguero

\brief      Constructor for the popup message data object sent to the systems

\param      message
            The message given to the user

*/
/******************************************************************************/
PopUpMessageData::PopUpMessageData(const std::string message) : m_Message(message)
{

}


/******************************************************************************/
/*!
           GetMessage

\author    John Salguero

\brief     Returns the message from the popup message

\return    m_Message
           The message shown to the user

*/
/******************************************************************************/
const std::string PopUpMessageData::GetMessage()
{
  return m_Message;
}