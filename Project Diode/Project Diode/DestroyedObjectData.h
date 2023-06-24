/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    DestroyedObjectData.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This header file defines the Data for the Component Destroyed Message
    which is used in response to certain actions, which send an event
    when an old component is destroyed that can be handled by systems.
*/
/********************************************************************/
#ifndef _DestroyedObjectData
#define _DestroyedObjectData

class Object; // forward declarations

class DestroyedObjectData : public std::enable_shared_from_this<DestroyedObjectData> {
public:
  //  Constructor
  DestroyedObjectData(std::shared_ptr<Object> const& newObject);

  // Default Destructor for Message Base Class
  virtual ~DestroyedObjectData() = default;

  // obtains the component
  std::weak_ptr<Object> GetObject();


private:
  // the Window Context
  std::shared_ptr<Object> m_Object;
};


#endif