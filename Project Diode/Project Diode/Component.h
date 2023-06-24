/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Component.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This header file declares the Component class, which is a class that
    defines the behavior of game objects. Different components do different
    things.

*/
/********************************************************************/
#ifndef _Component
#define _Component

// forward declarations
class Object;

using ComponentID = unsigned long;

enum class ComponentType {
  Collider,
  Renderable,
  RigidBody,
  Transform,
  Controller,
  Camera, 
  Teleportal
};

class Component : public std::enable_shared_from_this<Component> {

  template<class cType, ComponentType eType> comrade class ComponentTypeFactory;

public:
  // Retrieves the Componet Type
  virtual ComponentType GetType() = 0;
protected:
  // Parent of the component
  std::weak_ptr<Object> mParent;
  // Type of the Component
  ComponentType m_Type;
private:
  // The ID of the component
  ComponentID m_ID;
};

#endif