/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    ComponentFactory.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This header file declares the ComponentFactory class, which is a class
    that creates and Manages Components. It is templated so that it may
    define a factory for all components, and inherits from a base class
    so that it may be in a container of components.

*/
/********************************************************************/
#ifndef _ComponentFactory
#define _ComponentFactory

class ComponentBaseFactory {

  // Private constructor, using the singleton pattern
  ComponentBaseFactory() = default;
public:
  // Pure Virtual function that returns a generic Component
  virtual std::shared_ptr<Component> CreateComponent() const = 0;
  // Pure Virtual function that retrurns an archetypical component
  virtual std::shared_ptr<Component> CreateArchetypeComponent() const = 0;
  // Virtual Destructor - good practice to remember
  virtual ~ComponentBaseFactory() = default;
  // Returns a new id for the Component
  ComponentID GetNewID() const { return m_ID++; }

private:
  static ComponentID m_ID;
};

template<typename ClassType, ComponentType eType>
class ComponentFactory : public ComponentBaseFactory {

  // Private constructor, using the singleton pattern
  ComponentFactory() = default;
public:
  // Virtual Destructor - good practice to remember
  virtual ~ComponentFactory() = default;
  // Creates a Component and sends a message
  [[nodiscard]] virtual std::shared_ptr<Component> CreateComponent() const
  {
    std::shared_ptr<Component> newComponent = std::shared_ptr<Component>(new ClassType);
    newComponent->m_Type = mType;
    newComponent->m_ID = GetNewID();
    auto data = new CreatedComponentData(newComponent, mType);
    Engine::RelayMessage(std::shared_ptr<Message>(new Message(L"Core", MessageType::ComponentCreated, data)));
    return newComponent;
  };
  // Creates a Component for archetype reasons No Message Sent
  [[nodiscard]] virtual std::shared_ptr<Component> CreateArchetypeComponent() const
  {
    std::shared_ptr<Component> newComponent = std::shared_ptr<Component>(new ClassType);
    newComponent->m_Type = mType;
    newComponent->m_ID = GetNewID();
    return newComponent;
  };
private:
  ComponentType mType = eType;
};

#endif // !_ObjectFactory
