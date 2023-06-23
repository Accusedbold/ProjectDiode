/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    System.h
  \author  John Salguero
  \date    June 21, 2023
  \brief
    This header file declares the System Class, which is used as
    an interface for the Systems that belong to the Game Engine
*/
/********************************************************************/
#ifndef _System
#define _System

// Base class for Systems
class  System
{
public:
  // Constructor to the system
  System(std::wstring& name) : m_SystemName(name) {}
  // Destructor - All systems should have a virtual destructor
  virtual ~System() {}

  // Updates the function on a per frame basis
  virtual void Update(double dt) = 0;

  // Releases the system and deletes all allocations
  virtual int Release() = 0;

  // Returns the name of the system for debugging
  virtual std::wstring GetName() const
  {
    return m_SystemName;
  }

  // Initializes the system
  virtual void Initialize() {}

protected:
  // Identifier for the System
  std::wstring const m_SystemName;
};

#endif