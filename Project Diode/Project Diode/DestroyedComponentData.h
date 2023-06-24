/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    DestroyedComponentData.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This header file defines the Data for the Component Destroyed Message
    which is used in response to certain actions, which send an event
    when an old component is destroyed that can be handled by systems.
*/
/********************************************************************/
#ifndef _DestroyedComponentData
#define _DestroyedComponentData

class Component; // forward declarations

class DestroyedComponentData : public std::enable_shared_from_this<DestroyedComponentData> {
public:
  //  Constructor
  DestroyedComponentData(std::shared_ptr<Component> const& newObject);

  // Default Destructor for Message Base Class
  virtual ~DestroyedComponentData() = default;

  // obtains the component
  std::weak_ptr<Component> GetComponent();


private:
  // the Window Context
  std::shared_ptr<Component> m_Component;
};


#endif