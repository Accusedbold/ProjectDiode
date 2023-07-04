/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    ObjectFactory.cpp
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This cpp file defines the ObjectFactory class member functions, 
    which is a class allow the object factory to create objects

*/
/********************************************************************/
#include "stdafx.h"

ObjectFactory* ObjectFactory::m_Instance = nullptr;
ComponentID ComponentBaseFactory::m_ID = 0;

/******************************************************************************/
/*!
          GetInstance

\author   John Salguero

\brief    Returns the single instance of the object factory

\return   ObjectFactory*
          The single instance of the object factory
*/
/******************************************************************************/
ObjectFactory* ObjectFactory::GetInstance()
{
  if (!m_Instance)
    m_Instance = new ObjectFactory;
  return m_Instance;
}

/******************************************************************************/
/*!
          InitializedUpdate

\author   John Salguero

\brief    Creates a Generic Object with no components

\return   std::weak_ptr<Object>
          pointer to the newly created object
*/
/******************************************************************************/
std::weak_ptr<Object> ObjectFactory::CreateGenericObject()
{
  /* Create The Object */
  std::shared_ptr<Object>retVal(new Object());
  retVal->m_ID = m_ID++;
  m_ObjectMap.insert(std::pair<ObjectID, std::shared_ptr<Object>>(retVal->m_ID, retVal));
  
  // Send the Message
  std::shared_ptr<Message>msg(new Message(L"Core", MessageType::ObjectCreated, retVal));
  Engine::GetInstance()->RelayMessage(msg);

  return retVal;
}

/******************************************************************************/
/*!
          CreateGenericArchetype

\author   John Salguero

\brief    Creates a generic object for use with archetypes

\param    ArchetypeName
          The name of the archetype

\return   std::weak_ptr<Object
          Pointer to the newly made object
*/
/******************************************************************************/
std::weak_ptr<Object> ObjectFactory::CreateGenericArchetype(const std::wstring& ArchetypeName)
{
  /* Create The Object */
  std::shared_ptr<Object> retVal(new Object());
  retVal->m_ArchetypeName = ArchetypeName;
  m_ArchetypeMap.insert(std::pair<std::wstring, std::shared_ptr<Object>>(ArchetypeName, retVal));

  return retVal;
}

/******************************************************************************/
/*!
          CreateArchetypedObject

\author   John Salguero

\brief    Given an Archetype's Name, creates that archetype

\param    ArchetypeName
          Name of the Archetype to instantiate

\return   std::weak_ptr<Object>
          Pointer to the newly made object
*/
/******************************************************************************/
std::weak_ptr<Object> ObjectFactory::CreateArchetypedObject(const std::wstring& ArchetypeName)
{
  std::weak_ptr<Object> retVal; /* the object to return */

  /* Archetype iterator */
  auto archeIT = m_ArchetypeMap.find(ArchetypeName);

  /* Make sure it actually exists */
  if (archeIT == m_ArchetypeMap.end())
  {
    NONFATAL_ERROR("Improper Archetype specified");
    return retVal;
  }

  /* Create The Archetype */
  retVal = (*archeIT).second->CloneObject();

  // Send the Message
  std::shared_ptr<Message>msg(new Message(L"Core", MessageType::ObjectCreated, retVal.lock()));
  Engine::GetInstance()->RelayMessage(msg);

  return retVal;
}

/******************************************************************************/
/*!
          CreateComponent

\author   John Salguero

\brief    Creates a Component

\param    compType
          The Component Type To Make

\return   std::shared_ptr<Component>
          pointer to the Component Created
*/
/******************************************************************************/
std::shared_ptr<Component> ObjectFactory::CreateComponent(ComponentType compType)
{
  /* Create The Component */
  std::shared_ptr<Component> retVal = m_ComponentFactoryMap.find(compType)->second->CreateComponent();

  return retVal;
}

/******************************************************************************/
/*!
          AddArchetype

\author   John Salguero

\brief    Adds an archetype to the map of archetypes

\param    ArchetypeName
          The name being given to the archetype

\param    obj
          the object that will become the archetype

\return   void
*/
/******************************************************************************/
void ObjectFactory::AddArchetype(const std::wstring& ArchetypeName, std::weak_ptr<Object> const& obj)
{
  m_ArchetypeMap[ArchetypeName] = obj.lock();
}

/******************************************************************************/
/*!
          AddComponentFactory

\author   John Salguero

\brief    Adds a Component Factory to the map of factories

\param    type
          The type of factory to add

\param    factory
          The factory to add

\return   void
*/
/******************************************************************************/
void ObjectFactory::AddComponentFactory(ComponentType type, 
  std::shared_ptr<ComponentBaseFactory> factory)
{
  m_ComponentFactoryMap[type] = factory;
}

/******************************************************************************/
/*!
          GiveObjectComponent

\author   John Salguero

\brief    given a component and object, gives the object the component

\param    object
          The Object that is getting the component

\param    component
          The Component given to the object

\return   std::weak_ptr<Component>
          pointer to the component being added to the object
*/
/******************************************************************************/
std::weak_ptr<Component> const ObjectFactory::GiveObjectComponent(
  std::weak_ptr<Object> const& object, std::weak_ptr<Component> const& component)
{
  object.lock()->AddComponent(component);
  component.lock()->m_Parent = object.lock();

  return component;
}

/******************************************************************************/
/*!
          GiveObjectComponent

\author   John Salguero

\brief    Given an object id and Component type, adds that component to the
          corressponding object

\param    ObjectID
          The id of the object

\param    ComponentType
          The type of the component

\return   std::weak_ptr<Component>
          pointer to the Component added to the object
*/
/******************************************************************************/
std::weak_ptr<Component> const ObjectFactory::GiveObjectComponent(ObjectID id, ComponentType type)
{
  auto newComponent = m_ComponentFactoryMap.find(type)->second->CreateComponent();
  auto object = m_ObjectMap.find(id);
  object->second->AddComponent(newComponent);
  newComponent->m_Parent = object->second;

  return newComponent;
}

/******************************************************************************/
/*!
          GiveObjectComponent

\author   John Salguero

\brief    Given the object and type of component, add that component to the
          object

\param    obj
          Object recieving the component

\param    type
          Type of component to make

\return   std::weak_ptr<Component>
          pointer to the newly created component
*/
/******************************************************************************/
std::weak_ptr<Component> const ObjectFactory::GiveObjectComponent(
  std::weak_ptr<Object> const& obj, ComponentType type)
{
  auto newComponent = m_ComponentFactoryMap.find(type)->second->CreateComponent();
  obj.lock()->AddComponent(newComponent);
  newComponent->m_Parent = obj;

  return newComponent;
}

/******************************************************************************/
/*!
          GiveObjectComponent

\author   John Salguero

\brief    Given an Object Id and a component, add that component to the object

\param    objID
          id of the object

\param    component
          component to add

\return   std::weak_ptr<Component>
          pointer to the component added
*/
/******************************************************************************/
std::weak_ptr<Component> const ObjectFactory::GiveObjectComponent(
  ObjectID objID, std::weak_ptr<Component> const& component)
{
  auto object = m_ObjectMap.find(objID);
  object->second->AddComponent(component);
  component.lock()->m_Parent = object->second;

  return component;
}

/******************************************************************************/
/*!
          GiveArchetypeComponent

\author   John Salguero

\brief    Gives an archetype object a component

\param    archetype
          The archetype object

\param    type
          Type of the component

\return   std::weak_ptr<Component>
          pointer to the newly made component
*/
/******************************************************************************/
std::weak_ptr<Component> const ObjectFactory::GiveArchetypeComponent(
  std::weak_ptr<Object> const& archetype, ComponentType type)
{
  auto newComponent = m_ComponentFactoryMap.find(type)->second->CreateArchetypeComponent();
  archetype.lock()->AddComponent(newComponent);
  newComponent->m_Parent = archetype;

  return newComponent;
}

/******************************************************************************/
/*!
          GiveArchetypeComponent

\author   John Salguero

\brief    Gives an archetype object a component

\param    archetypeName
          The name of the archetype

\param    type
          Type of the component

\return   std::weak_ptr<Component>
          The pointer to the newly created Component
*/
/******************************************************************************/
std::weak_ptr<Component> const ObjectFactory::GiveArchetypeComponent(
  const std::wstring& archetypeName, ComponentType type)
{
  auto archetype = m_ArchetypeMap.find(archetypeName)->second;
  auto component = m_ComponentFactoryMap[type]->CreateArchetypeComponent();
  archetype->AddComponent(component);
  component->m_Parent = archetype;

  return component;
}

/******************************************************************************/
/*!
          GiveArchetypeComponent

\author   John Salguero

\brief    Gives an archetype object a component

\param    object
          Object that will be given the component

\param    component
          Component being given to the object

\return   std::weak_ptr<Component>
          pointer to the component given to the object
*/
/******************************************************************************/
std::weak_ptr<Component> const ObjectFactory::GiveArchetypeComponent(
  std::weak_ptr<Object> const& object, std::weak_ptr<Component> const& component)
{
  object.lock()->AddComponent(component);
  component.lock()->m_Parent = object;

  return component;
}

/******************************************************************************/
/*!
          GiveArchetypeComponent

\author   John Salguero

\brief    Gives an archetype object a component

\param    archetypeName
          name of the archetype being given an object

\param    component
          Component being given to the object

\return   std::weak_ptr<Component>
          pointer to the component given to the object
*/
/******************************************************************************/
std::weak_ptr<Component> const ObjectFactory::GiveArchetypeComponent(
  const std::wstring& archetypeName, std::weak_ptr<Component> const& component)
{
  auto object = m_ArchetypeMap[archetypeName];
  object->AddComponent(component);
  component.lock()->m_Parent = object;

  return component;
}

/******************************************************************************/
/*!
          Destroy

\author   John Salguero

\brief    Given an object, destroys that object

\param    object
          The object to destroy

\return   void
*/
/******************************************************************************/
void ObjectFactory::Destroy(std::weak_ptr<Object> const& object)
{
  // Destroy the object
  Destroy(object.lock()->GetID());
}

/******************************************************************************/
/*!
          Destroy

\author   John Salguero

\brief    Given an object id, destroys that object

\param    objectID
          The object to destroy

\return   void
*/
/******************************************************************************/
void ObjectFactory::Destroy(ObjectID objectID)
{
  // Destroy the object
  auto mapIT = m_ObjectMap.find(objectID);
  if (mapIT != m_ObjectMap.end())
  {
    // send the message
    auto sharedObject = mapIT->second;
    sharedObject->Release();
    std::shared_ptr<Message> msg(new Message(L"Core", MessageType::ObjectDestroyed, sharedObject));
    Engine::GetInstance()->RelayMessage(msg);
    for (auto& comp : mapIT->second->m_Components)
    {
      std::shared_ptr<Message> componentMessage(new Message(L"Core", MessageType::ComponentDestroyed, comp.second));
      Engine::GetInstance()->RelayMessage(componentMessage);
    }

    m_ObjectMap.erase(mapIT);
  }
}

/******************************************************************************/
/*!
          InitializedUpdate

\author   John Salguero

\brief    Destroys all the Objects

\return   void
*/
/******************************************************************************/
void ObjectFactory::DestroyAllObjects()
{
  while (!m_ObjectMap.empty())
    Destroy(m_ObjectMap.begin()->second);
}

/******************************************************************************/
/*!
          DestroyArchetype

\author   John Salguero

\brief    Destroys an archetype by name

\param    archetypeName
          The name of the archetype to destroy

\return   void
*/
/******************************************************************************/
void ObjectFactory::DestroyArchetype(const std::wstring& archetypeName)
{
  // Destroy the object
  auto mapIT = m_ArchetypeMap.find(archetypeName);
  if (mapIT != m_ArchetypeMap.end())
  {
    m_ArchetypeMap.erase(mapIT);
  }
}

/******************************************************************************/
/*!
          InitializedUpdate

\author   John Salguero

\brief    The Update function after the device is properly initialized

\param    dt
          The delta in time since last game tick

\return   void
*/
/******************************************************************************/
void ObjectFactory::DestroyAllArchetypes()
{
  m_ArchetypeMap.clear();
}

/******************************************************************************/
/*!
          Release

\author   John Salguero

\brief    Releases all of the resources

\return   int
          The error code. 0 is success
*/
/******************************************************************************/
int ObjectFactory::Release()
{
  DestroyAllArchetypes();
  DestroyAllObjects();
  m_ComponentFactoryMap.clear();

  return 0;
}

/******************************************************************************/
/*!
          Update

\author   John Salguero

\brief    RUpdates all the objects

\return   dt
          The duration between game tics
*/
/******************************************************************************/
void ObjectFactory::Update(double dt)
{
  for (auto& object : m_ObjectMap)
    object.second->Update(dt);
}
