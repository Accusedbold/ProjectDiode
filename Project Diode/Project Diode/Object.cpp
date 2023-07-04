/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Object.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This cpp file defines the Object class functions, which is a class
    that 
    holds the different components that define each of the entities
    in the game. This uses the Enity Component System (ECS) software
    architectural pattern.

*/
/********************************************************************/
#include "stdafx.h"

/******************************************************************************/
/*!
           Initialize

\author    John Salguero

\brief     Initializes the object

\return    void

*/
/******************************************************************************/
void Object::Initialize()
{
  for (auto it = m_Components.begin(), end = m_Components.end(); it != end; ++it)
  {
    it->second->m_Parent = shared_from_this();
    it->second->Initialize();
  }
}

/******************************************************************************/
/*!
           Update

\author    John Salguero

\brief     Updates each component

\return    void

*/
/******************************************************************************/
void Object::Update(double dt)
{
  for (auto& comp : m_Components)
  {
    comp.second->Update(dt);
  }
}

/******************************************************************************/
/*!
           AddComponent

\author    John Salguero

\brief     Adds a component to the Object object

\param     component
           The component to add

\return    void

*/
/******************************************************************************/
void Object::AddComponent(std::weak_ptr<Component> const& component)
{
  auto addComp = component.lock();

  auto compIT = m_Components.find(addComp->GetType());
  if (compIT != m_Components.end())
  {
    std::shared_ptr<Message>msg(new Message(L"Core", MessageType::ComponentDestroyed, component.lock()));
    Engine::GetInstance()->RelayMessage(msg);
  }

  m_Components[addComp->GetType()] = addComp;
}

/******************************************************************************/
/*!
           CloneObject

\author    John Salguero

\brief     Makes a clone of the object

\return    void

*/
/******************************************************************************/
std::weak_ptr<Object> Object::CloneObject() const
{
  std::shared_ptr<Object> ObjectClone = ObjectFactory::GetInstance()->CreateGenericObject().lock();

  for (auto it = m_Components.begin(), end = m_Components.end(); it != end; ++it)
  {
    ObjectClone->AddComponent(it->second->CloneComponent());
  }

  ObjectClone->Initialize();
  return ObjectClone;
}

/******************************************************************************/
/*!
           GetID

\author    John Salguero

\brief     Returns the id of the object

\return    mID
           The id of the object

*/
/******************************************************************************/
ObjectID Object::GetID() const
{
  return m_ID;
}

/******************************************************************************/
/*!
           Release

\author    John Salguero

\brief     Releases the object and its components

\return    void
*/
/******************************************************************************/
void Object::Release()
{
  for (auto& comp : m_Components)
  {
    comp.second->Release();
  }
}

/******************************************************************************/
/*!
           GetComponent

\author    John Salguero

\brief     Returns a component if the object has one 

\param     type
           The type of the component to get

\return    std::weak_ptr<Component>
           Pointer to the component
*/
/******************************************************************************/
std::weak_ptr<Component> Object::GetComponent(ComponentType type) const
{
  auto it = m_Components.find(type);
  if(it == m_Components.end())
    return std::weak_ptr<Component>();

  return it->second;
}
