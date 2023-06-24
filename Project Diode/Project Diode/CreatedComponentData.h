/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    CreatedComponent.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This header file defines the Data for the Component Created Message
    which is used in response to certain actions, which send an event
    when a new component is created that can be handled by systems.
*/
/********************************************************************/
#ifndef _CreatedComponentData
#define _CreatedComponentData

class Component; // forward declarations
enum class ComponentType;

class CreatedComponentData : public std::enable_shared_from_this<CreatedComponentData>  {
public:
  //  Constructor
  CreatedComponentData(std::weak_ptr<Component> const& newComponent, ComponentType componentType);

  // Default Destructor for Message Base Class
  virtual ~CreatedComponentData() = default;

  // obtains the component
  std::weak_ptr<Component> GetComponent();

  // obtains the type
  ComponentType GetType();
  

private:
  // the Window Context
  std::weak_ptr<Component> m_Component;
  ComponentType m_Type;
};


#endif