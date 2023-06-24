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
    std::shared_ptr<DestroyedComponentData>data(new DestroyedComponentData(component.lock()));
    std::shared_ptr<Message>msg(new Message(L"Core", MessageType::ComponentDestroyed, data));
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
