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
  WindowCreated,
  ErrorMessage,
  Quit,
  Shutdown
};

// Base class for Messages
class Message : public std::enable_shared_from_this<Message>
{
public:
  // Constructor for Message Base Class
  Message(std::wstring const& system, MessageType id, std::shared_ptr<void> const& data = nullptr);

  // Default Destructor for Message Base Class
  virtual ~Message() = default;

  // Get the type of message it is
  MessageType GetMessageId() const;

  // Get the name of the system that sent the message
  const std::wstring GetOriginatingSystem() const;

  // Get the data in the message
  const std::shared_ptr<void> GetData() const;

protected:
  // The type that the message is
  MessageType m_MessageId;
  // What System the message originates from
  std::wstring const m_FromSystem;
  // The Data Carried with the message
  std::shared_ptr<void> m_Data;
};

// Easy way to get the data from the message
#define GET_DATA_FROM_MESSAGE(type, msg) std::static_pointer_cast<type>(msg->GetData())

#endif