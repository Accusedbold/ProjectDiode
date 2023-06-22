/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Message.h
  \author  John Salguero
  \date    June 21, 2023
  \brief
    This header file defines the Message Class, which is used in response to certain
    actions, which send an event that can be handled
*/
/********************************************************************/
#ifndef _Messages // Code is included only once
#define _Messages

enum class MessageType
{
  None,
  ErrorMessage,
  Quit,
  Shutdown
};

// Base class for Messages
class Message : public std::enable_shared_from_this<Message>
{
public:
  // Conversion Constructor for Message Base Class
  Message(std::wstring const& system, MessageType id) : mMessageId(id), mFromSystem(system)
  {}

  // Default Destructor for Message Base Class
  virtual ~Message()
  {}

  // Get the type of message it is
  MessageType GetMessageId() const { return mMessageId; }

  virtual Message& operator=(Message const& rhs) { mMessageId = rhs.mMessageId; return *this; }

protected:
  // The type that the message is
  MessageType mMessageId;
  // What System the message originates from
  std::wstring const mFromSystem;
  // The Data Carried with the message
  std::shared_ptr<void> data;
};

#endif