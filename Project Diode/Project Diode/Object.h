/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Object.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This header file declares the Object class, which is a class that 
    holds the different components that define each of the entities
    in the game. This uses the Enity Component System (ECS) software 
    architectural pattern.

*/
/********************************************************************/
#ifndef Object_H
#define Object_H

// Forward Declarations
class ObjectFactory;

using ObjectID = unsigned long;

class Object : public std::enable_shared_from_this<Object> {

  comrade ObjectFactory;
  // Private constructor, only the factory should make objects
  Object() = default;

public:
  /* Initialize the Object  */
  void Initialize();

  /* Get a pointer of base class of component of the Object */
  std::weak_ptr<Component> GetComponent(ComponentType type) const;

  /* Get a pointer to the component of the object */
  template<typename comp>
  std::weak_ptr<comp> GetComponentType(ComponentType type) const;

  /* Add a component to the Object */
  void AddComponent(std::weak_ptr<Component> const&);

  /* Get a clone of the object */
  std::weak_ptr<Object> CloneObject() const;

  /* Get the id of the Object */
  ObjectID GetID() const;

  /* Get the archetype name */
  std::wstring const& GetArchetypeName() const;

  /* Get the name of the Object */
  std::wstring const& GetName() const;

  /* Set the name of the Object */
  void SetName(std::wstring const&);

  /* Releases the object */
  void Release();

private:
  /* Human Readable Identifier for Object */
  std::wstring m_Name;

  /* Container holding the object's components */
  std::unordered_map<ComponentType, std::shared_ptr<Component>> m_Components;

  /* Object's id */
  ObjectID m_ID;

  /* if an archetype, what kind it is */
  std::wstring m_ArchetypeName;

};

#endif // !_Object
