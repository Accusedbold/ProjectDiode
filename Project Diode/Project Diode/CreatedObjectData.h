/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    CreatedObjectData.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This header file defines the Data for the Component Created Message
    which is used in response to certain actions, which send an event
    when a new component is created that can be handled by systems.
*/
/********************************************************************/
#ifndef _CreatedObjectData
#define _CreatedObjectData

class Object; // forward declarations

class CreatedObjectData : public std::enable_shared_from_this<CreatedObjectData> {
public:
  //  Constructor
  CreatedObjectData(std::weak_ptr<Object> const& newObject);

  // Default Destructor for Message Base Class
  virtual ~CreatedObjectData() = default;

  // obtains the component
  std::weak_ptr<Object> GetObject();


private:
  // the Window Context
  std::weak_ptr<Object> m_Object;
};


#endif