/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Callable.h
  \author  John Salguero
  \date    June 22, 2023
  \brief
    This header file declares the Callable class, which is a class that
    can use the () operator to call it with a smart pointer of a
    message. This is used to handle messages.
*/
/********************************************************************/
#ifndef _Callable
#define _Callable

// forward declaration
class Message;

class Callable
{
public:
  // Constructor
  Callable(long long id, std::function<void(std::shared_ptr<Message> const&)>);
  // Copy Constructor
  Callable(Callable const&) = default;
  // calling operator
  void operator()(std::shared_ptr<Message> const& msg) const;
  // equality operator
  bool operator==(Callable const& rhs) const;

private:
  // the id of the callable
  long long mId;
  // the function to call
  std::function<void(std::shared_ptr<Message> const&)> mFunction;
};

#endif
