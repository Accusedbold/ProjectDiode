/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Callable.cpp
  \author  John Salguero
  \date    June 22, 2023
  \brief
    This cpp file defines the Callable class member functions,
    allow for the message system to react to messages
*/
/********************************************************************/
#include "stdafx.h"

/******************************************************************************/
/*!
          Callable

\author   John Salguero

\brief    Constructor to the Callable

\param    fxn
          The fxn to make a Callable

\return   void

*/
/******************************************************************************/
Callable::Callable(long id, std::function<void(std::shared_ptr<Message> const&)> fxn)
{
  mId = id;
  mFunction = fxn;
}

/******************************************************************************/
/*!
          Callable

\author   John Salguero

\brief    MoveConstructor to the callable object

\param    newMessage
          A pointer to allocated memmory for a message - the core will
          take care of deleting this object.

\return   void

*/
/******************************************************************************/
Callable::Callable(Callable&& rhs)
{
  mId = rhs.mId;
  mFunction = rhs.mFunction;
}

/******************************************************************************/
/*!
          operator()

\author   John Salguero

\brief    function call operator

\param    msg
          The message to send to the function

\return   void

*/
/******************************************************************************/
void Callable::operator()(std::shared_ptr<Message> const& msg)
{
  mFunction(msg);
}

/******************************************************************************/
/*!
          operator==

\author   John Salguero

\brief    equality operator

\param    rhs
          What we are comparing the callable to.

\return   void

*/
/******************************************************************************/
bool Callable::operator==(Callable const& rhs)
{
  return (rhs.mId == mId);
}
